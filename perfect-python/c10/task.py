# -*- coding: utf-8 -*-
class Task:
    def __init__(self, name, due_date, required_time):
        self.name = name
        self.due_date = due_date
        self.required_time = required_time
        self.finished = False

    def __format__(self, spec):
        state = "完了" if self.finished else "未完了"
        format = "{state} {task.name}: {task.due_date:%Y-%m-%d}まで 予定所要時間 {task.required_time}分"
        return format.format(task=self, state=state)

    def finish(self):
        self.finished = True
