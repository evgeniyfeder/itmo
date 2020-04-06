import pytest
import unittest.mock as mock
from report.db_driver import ReportDbDriver
from datetime import datetime, timedelta


@pytest.fixture
def db_mock():
    mock_self = ReportDbDriver.__new__(ReportDbDriver)
    mock_self.con = mock.MagicMock()

    return mock_self


@pytest.fixture
def datetime_object():
    datetime_str = '03/26/18 17:55:26'
    datetime_object = datetime.strptime(datetime_str, '%m/%d/%y %H:%M:%S')

    return datetime_object


def test_avg_visit_duration_and_count(db_mock, datetime_object):
    mock_cursor = mock.MagicMock()
    db_mock.con.cursor.return_value.__enter__.return_value = mock_cursor

    # one event
    mock_cursor.__iter__.return_value = [
        (1, 0, datetime_object, 'enter'),
        (1, 1, datetime_object + timedelta(hours=1), 'exit')
    ]
    assert db_mock.avg_visit_duration_and_count(datetime_object) == {'avg_cnt': 1, 'avg_time_s': 3600.}

    # one not finished
    mock_cursor.__iter__.return_value = [
        (1, 0, datetime_object, 'enter'),
        (2, 0, datetime_object, 'enter'),
        (1, 1, datetime_object + timedelta(hours=1), 'exit')
    ]
    assert db_mock.avg_visit_duration_and_count(datetime_object) == {'avg_cnt': 1, 'avg_time_s': 3600.}

    # two separated
    mock_cursor.__iter__.return_value = [
        (1, 0, datetime_object, 'enter'),
        (2, 0, datetime_object, 'enter'),
        (1, 1, datetime_object + timedelta(hours=1), 'exit'),
        (2, 1, datetime_object + timedelta(hours=2), 'exit')
    ]
    assert db_mock.avg_visit_duration_and_count(datetime_object) == {'avg_cnt': 1, 'avg_time_s': 5400.}

    # two events per one user
    mock_cursor.__iter__.return_value = [
        (1, 0, datetime_object, 'enter'),
        (1, 1, datetime_object + timedelta(hours=1), 'exit'),
        (1, 2, datetime_object + timedelta(hours=2), 'enter'),
        (1, 3, datetime_object + timedelta(hours=4), 'exit')
    ]
    assert db_mock.avg_visit_duration_and_count(datetime_object) == {'avg_cnt': 2, 'avg_time_s': 5400.}


def test_all_visit_by_day(db_mock, datetime_object):
    mock_cursor = mock.MagicMock()
    db_mock.con.cursor.return_value.__enter__.return_value = mock_cursor

    # one event
    mock_cursor.__iter__.return_value = [
        (1, 0, datetime_object, 'enter'),
        (1, 1, datetime_object + timedelta(hours=1), 'exit')
    ]
    assert db_mock.all_visit_by_day(datetime_object) == {'Friday': 0,
                                                         'Monday': 1,
                                                         'Saturday': 0,
                                                         'Sunday': 0,
                                                         'Thursday': 0,
                                                         'Tuesday': 0,
                                                         'Wednesday': 0}

    # we count not ended events
    mock_cursor.__iter__.return_value = [
        (1, 0, datetime_object, 'enter'),
        (2, 0, datetime_object, 'enter'),
        (1, 1, datetime_object + timedelta(hours=1), 'exit')
    ]
    assert db_mock.all_visit_by_day(datetime_object) == {'Friday': 0,
                                                         'Monday': 2,
                                                         'Saturday': 0,
                                                         'Sunday': 0,
                                                         'Thursday': 0,
                                                         'Tuesday': 0,
                                                         'Wednesday': 0}

    mock_cursor.__iter__.return_value = [
        (1, 0, datetime_object, 'enter'),
        (2, 0, datetime_object, 'enter'),
        (1, 1, datetime_object + timedelta(hours=1), 'exit'),
        (2, 1, datetime_object + timedelta(hours=2), 'exit'),
        (2, 2, datetime_object + timedelta(days=1), 'enter')
    ]
    assert db_mock.all_visit_by_day(datetime_object) == {'Friday': 0,
                                                         'Monday': 2,
                                                         'Saturday': 0,
                                                         'Sunday': 0,
                                                         'Thursday': 0,
                                                         'Tuesday': 1,
                                                         'Wednesday': 0}
