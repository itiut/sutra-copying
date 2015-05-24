# -*- coding: utf-8 -*-
class TaskManager:
    def __init__(self, db):
        self.db = db

    def add(self, task):
        key = self.__next_task_key()
        self.db[key] = task

    def __next_task_key(self):
        id = self.db.get('next_id', 0)
        self.db['next_id'] = id + 1
        return "task:{0}".format(id)

    def all(self):
        for key in self.db:
            if key.startswith('task:'):
                yield key, self.db[key]

    def unfinished(self):
        return ((key, task) for key, task in self.all() if not task.finished)

    def finish(self, key):
        task = self.db[key]
        task.finish()
        self.db[key] = task

    def __enter__(self):
        return self

    def __exit__(self, type, value, tb):
        self.db.close()
