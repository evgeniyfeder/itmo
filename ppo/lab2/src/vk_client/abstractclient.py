from abc import abstractmethod
from typing import Dict


class AbstractVkClient:
    @property
    @abstractmethod
    def access_token(self):
        raise NotImplementedError

    @property
    @abstractmethod
    def api_version(self):
        raise NotImplementedError

    @abstractmethod
    async def execute_method(self, method_name: str, parameters: Dict[str, str]):
        raise NotImplementedError

    @abstractmethod
    def close(self):
        raise NotImplementedError

class VkApiError(Exception):
    pass