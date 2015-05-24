#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import argparse
import shelve
from datetime import datetime

from task import Task
from task_manager import TaskManager


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('shelve')

    subparsers = parser.add_subparsers()
    add_parser = subparsers.add_parser('add')
    add_parser.set_defaults(func=cmd_add)
    list_parser = subparsers.add_parser('list')
    list_parser.add_argument('-a', '--all', action="store_true")
    list_parser.set_defaults(func=cmd_list)
    finish_parser = subparsers.add_parser('finish')
    finish_parser.add_argument('task')
    finish_parser.set_defaults(func=cmd_finish)

    args = parser.parse_args()

    db = shelve.open(args.shelve, 'c')
    with TaskManager(db) as manager:
        args.manager = manager
        if hasattr(args, 'func'):
            args.func(args)
        else:
            args.parser.print_help()


def cmd_add(args):
    name = input('task name:')
    due_date = datetime.strptime(input('due date [Y-m-d]:'), '%Y-%m-%d')
    required_time = int(input('required_time:'))

    task = Task(name, due_date, required_time)
    args.manager.add(task)


def cmd_list(args):
    if args.all:
        tasks = args.manager.all()
    else:
        tasks = args.manager.unfinished()

    for key, task in tasks:
        print("{0} {1}".format(key, format(task)))


def cmd_finish(args):
    args.manager.finish(args.task)


if __name__ == '__main__':
    main()
