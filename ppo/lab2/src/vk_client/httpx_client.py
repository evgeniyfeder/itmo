import httpx
import typing
import logging
import attr
from datetime import datetime
import typing
import time

from vk_client.abstractclient import AbstractVkClient, VkApiError


logger = logging.getLogger(__name__)


class HttpxVkClient(AbstractVkClient):
    def __init__(self,
                 access_token: str,
                 api_version: str = "5.52",
                 base_url=httpx.URL("https://api.vk.com"),
                 app: typing.Callable = None):
        self.client = httpx.Client(base_url=base_url, app=app)
        self._api_version = api_version
        self._access_token = access_token

    @property
    def access_token(self):
        return self._access_token

    @property
    def api_version(self):
        return self._api_version

    async def execute_method(self, method_name: str, params: typing.Dict[str, str]):
        params.update({"access_token": self.access_token})
        params.update({"v": self.api_version})

        r = await self.client.get(f"/method/{method_name}", params=params)

        j = r.json()
        logger.debug(f"Received text: {j}")

        if "error" in j:
            raise VkApiError(f"Error code={j['error']['error_code']}. {j['error']['error_msg']}")
        if "response" in j:
            return j["response"]

    async def close(self):
        await self.client.close()


@attr.s(auto_attribs=True)
class NewsfeedSearchResponse:
    id: int
    owner_id: int
    from_id: int
    date: datetime
    text: str
    comments_count: int
    likes_count: int
    reposts_count: int

    @classmethod
    def from_json(cls, json):
        return cls(
            id=json['id'],
            owner_id=json['owner_id'], from_id=json['from_id'],
            date=datetime.fromtimestamp(json['date']), text=json['text'],
            comments_count=json['comments']['count'],
            likes_count=json['likes']['count'],
            reposts_count=json['reposts']['count'],
        )


async def search_posts(vk_client: HttpxVkClient,
                       pattern: str,
                       count: int) \
        -> typing.List[NewsfeedSearchResponse]:
    response = await vk_client.execute_method(method_name="newsfeed.search", params={"q": pattern, "count": count})
    return [NewsfeedSearchResponse.from_json(j) for j in response["items"]]
