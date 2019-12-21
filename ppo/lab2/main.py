import argparse
from contextlib import closing
import pathlib
import asyncio

from vk_client.httpx_client import search_posts, HttpxVkClient


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("-p", "--pattern", help="Pattern to search in my newsfeed")
    parser.add_argument("-t", "--token", type=pathlib.Path, default=pathlib.Path("access_token"),
                        help="path to credentionals")
    parser.add_argument("-c", "--count", help="count of posts that we want")
    args = parser.parse_args()

    with args.token.open('rt') as token_file:
        try:
            client = HttpxVkClient(access_token=token_file.readline())
            posts = asyncio.run(search_posts(vk_client=client, pattern=args.pattern, count=args.count))

            for p in posts:
                print("========================================")
                print(p.text)
        finally:
            asyncio.run(client.close())


if __name__ == '__main__':
    main()
