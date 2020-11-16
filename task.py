from time import sleep
from celery import Celery

app = Celery('tasks', broker='pyamqp://guest@localhost//')

@app.task
def add(x, y):
    print('[+] Starting task')
    sleep(10)
    print(x + y)
