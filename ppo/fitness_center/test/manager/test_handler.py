import pytest
import unittest.mock as mock
from manager.handler import ManagerHandler
from datetime import datetime, timedelta
from manager.db_objects import UserSubscription
from manager.requests import UpdateSubscriptionCommand
from fastapi.exceptions import HTTPException

@pytest.fixture
def handler_mock():
    mock_self = ManagerHandler.__new__(ManagerHandler)
    mock_self.db = mock.MagicMock()

    return mock_self


@pytest.fixture
def datetime_object():
    datetime_str = '03/26/18 17:55:26'
    datetime_object = datetime.strptime(datetime_str, '%m/%d/%y %H:%M:%S')

    return datetime_object


def test_update_subscription_command(handler_mock, datetime_object):
    handler_mock.db.get_user_subscription_event.return_value = UserSubscription(user_id=30, event_id=239,
                                                                                end_date=datetime_object)
    with pytest.raises(HTTPException):
        handler_mock.handle_command(UpdateSubscriptionCommand(30, datetime_object - timedelta(hours=1)))
    handler_mock.handle_command(UpdateSubscriptionCommand(30, datetime_object + timedelta(hours=1)))
