import pytest
import unittest.mock as mock
from turnstile.db_driver import TurnstileDbDriver
from turnstile.db_objects import TurnstileEvent, TurnstileStatus
from datetime import datetime, timedelta


@pytest.fixture
def db_mock():
    mock_self = TurnstileDbDriver.__new__(TurnstileDbDriver)
    mock_self.con = mock.MagicMock()

    return mock_self


@pytest.fixture
def datetime_object():
    datetime_str = '03/26/18 17:55:26'
    datetime_object = datetime.strptime(datetime_str, '%m/%d/%y %H:%M:%S')

    return datetime_object


def test_get_last_turnstile_event(db_mock, datetime_object):
    mock_cursor = mock.MagicMock()
    db_mock.con.cursor.return_value.__enter__.return_value = mock_cursor

    mock_cursor.fetchone.return_value = (30, 239, datetime_object, 'enter')
    assert db_mock.get_last_turnstile_event(1) == TurnstileEvent(user_id=30, event_id=239,
                                                                 event_timestamp=datetime_object,
                                                                 event_type=TurnstileStatus.enter)



