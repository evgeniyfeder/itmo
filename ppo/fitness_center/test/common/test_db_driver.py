import pytest
import unittest.mock as mock
from common.db_driver import PSQLDbDriver
from datetime import datetime, timedelta
from manager.db_objects import UserSubscription


@pytest.fixture
def db_mock():
    mock_self = PSQLDbDriver.__new__(PSQLDbDriver)
    mock_self.con = mock.MagicMock()

    return mock_self


def test_max_user_event_id(db_mock):
    mock_cursor = mock.Mock()
    db_mock.con.cursor.return_value.__enter__.return_value = mock_cursor

    mock_cursor.fetchone.return_value = (5,)
    assert db_mock.get_max_user_event_id(42) == 5

    mock_cursor.fetchone.return_value = (None,)
    assert db_mock.get_max_user_event_id(30) == -1


@pytest.fixture
def datetime_object():
    datetime_str = '03/26/18 17:55:26'
    datetime_object = datetime.strptime(datetime_str, '%m/%d/%y %H:%M:%S')

    return datetime_object


def test_get_user_subscription_event(db_mock, datetime_object):
    mock_cursor = mock.MagicMock()
    db_mock.con.cursor.return_value.__enter__.return_value = mock_cursor

    mock_cursor.fetchone.return_value = (30, 239, datetime_object)
    assert db_mock.get_user_subscription_event(1) == UserSubscription(user_id=30, event_id=239,
                                                                      end_date=datetime_object)
