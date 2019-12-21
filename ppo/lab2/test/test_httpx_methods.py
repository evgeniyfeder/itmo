import pytest
import logging
from fastapi import FastAPI
from starlette.responses import JSONResponse
from fastapi import Query

from vk_client.httpx_client import HttpxVkClient, search_posts
from vk_client.abstractclient import VkApiError

logger = logging.getLogger(__name__)
logger.setLevel(logging.DEBUG)

app = FastAPI()


@app.on_event("startup")
async def startup():
    logger.debug("starting the app")


@app.on_event("shutdown")
async def shutdown():
    logger.debug("shutdown the app")


@app.get("/method/newsfeed.search")
def newsfeed_search(access_token: str, v: str):
    logger.debug(access_token)
    return JSONResponse(
        {
            "response":
                {
                    "items": [
                        {
                            "id": 1434,
                            "date": 1576947441,
                            "owner_id": 271993503,
                            "from_id": 271993503,
                            "post_type": "post",
                            "text": "Сколько песику ? | f3.cool/k_podvitelskaya",
                            "comments": {
                                "count": 0,
                                "can_post": 1,
                                "groups_can_post": True
                            },
                            "likes": {
                                "count": 0,
                                "user_likes": 0,
                                "can_like": 1,
                                "can_publish": 1
                            },
                            "reposts": {
                                "count": 0,
                                "user_reposted": 0
                            }
                        }
                    ]
                }
        })


@app.get("/method/messages.send")
def messages_send(user_id: int):
    return JSONResponse({"response": str(user_id)})


@app.get("/method/messages.pin")
def messages_pin():
    return JSONResponse(
        {
            "error":
                {
                    "error_code": 100,
                    "error_msg": "One of the parameters specified was missing or invalid: peer_id is undefined"
                }
        })


@pytest.fixture("package")
def client(request):
    with open("access_token", "rt") as ac_tok_f:
        client = HttpxVkClient(access_token=ac_tok_f.readline(), app=app)

    def fin():
        logger.info("Closing client connection")
        client.close()

    request.addfinalizer(fin)

    yield client


@pytest.mark.asyncio
async def test_client_response(client):
    res = await client.execute_method("messages.send", {"user_id": "322"})
    assert res == "322"


@pytest.mark.asyncio
async def test_search_posts(client):
    res = await search_posts(vk_client=client,
                                        pattern="Из Китая",
                                        count=1)
    assert len(res) == 1
    assert res[0].id == 1434
    assert res[0].likes_count == 0


@pytest.mark.asyncio
async def test_client_fail(client):
    with pytest.raises(VkApiError):
        await client.execute_method("messages.pin", {"peer_id": 322})
