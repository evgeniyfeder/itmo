# Фитнес-центр

## Как запустить
```bash
PYTHONPATH=$PWD/src poetry run uvicorn manager.server:app --workers 1 --port 1111 --http httptools --reload
PYTHONPATH=$PWD/src poetry run uvicorn turnstile.server:app --workers 1 --port 2222 --http httptools --reload
PYTHONPATH=$PWD/src poetry run uvicorn report.server:app --workers 1 --port 3333 --http httptools --reload
```

## Пример запросов
```bash
curl -i --request POST http://127.0.0.1:1111/update_subscription\?user_id\=2\&until_date\=2020-12-12+12:12  
curl -i --request GET http://127.0.0.1:1111/get_user\?user_id\=2     
curl -i --request GET http://127.0.0.1:2222/enter\?user_id\=1   
curl -i --request GET http://127.0.0.1:2222/exit\?user_id\=1
curl -i --request POST http://127.0.0.1:3333/report 
```