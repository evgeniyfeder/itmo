import pytest
import unittest.mock as mock
from datetime import datetime, timedelta
from turnstile.handler import TurnstileHandler
from turnstile.requests import ExitCommand, EnterCommand
from turnstile.db_objects import TurnstileEvent, TurnstileStatus
from fastapi.exceptions import HTTPException
from manager.db_objects import UserSubscription


@pytest.fixture
def handler_mock():
    mock_self = TurnstileHandler.__new__(TurnstileHandler)
    mock_self.db = mock.MagicMock()

    return mock_self


@pytest.fixture
def datetime_object():
    datetime_str = '03/26/18 17:55:26'
    datetime_object = datetime.strptime(datetime_str, '%m/%d/%y %H:%M:%S')

    return datetime_object


def test_enter_after_enter(handler_mock, datetime_object):
    handler_mock.db.get_last_turnstile_event.return_value = TurnstileEvent(user_id=30, event_id=239,
                                                                           event_timestamp=datetime_object,
                                                                           event_type=TurnstileStatus.enter)
    with pytest.raises(HTTPException):
        handler_mock.handle_command(EnterCommand(30, datetime_object + timedelta(hours=1)))


def test_enter_without_sub(handler_mock, datetime_object):
    handler_mock.db.get_user_subscription_event.return_value = UserSubscription(user_id=30, event_id=239,
                                                                                end_date=datetime_object)

    with pytest.raises(HTTPException):
        handler_mock.handle_command(EnterCommand(30, datetime_object + timedelta(hours=1)))


def test_enter_normal(handler_mock, datetime_object):
    handler_mock.db.get_last_turnstile_event.return_value = TurnstileEvent(user_id=30, event_id=239,
                                                                           event_timestamp=datetime_object - timedelta(
                                                                               hours=1),
                                                                           event_type=TurnstileStatus.exit)

    handler_mock.db.get_user_subscription_event.return_value = UserSubscription(user_id=30, event_id=228,
                                                                                end_date=datetime_object + timedelta(
                                                                                    hours=1))

    handler_mock.handle_command(EnterCommand(30, datetime_object))


def test_exit_after_exit(handler_mock, datetime_object):
    handler_mock.db.get_last_turnstile_event.return_value = TurnstileEvent(user_id=30, event_id=239,
                                                                           event_timestamp=datetime_object,
                                                                           event_type=TurnstileStatus.exit)
    with pytest.raises(HTTPException):
        handler_mock.handle_command(ExitCommand(30, datetime_object + timedelta(hours=1)))


def test_first_exit(handler_mock, datetime_object):
    handler_mock.db.get_last_turnstile_event.return_value = None
    with pytest.raises(HTTPException):
        handler_mock.handle_command(ExitCommand(30, datetime_object + timedelta(hours=1)))
