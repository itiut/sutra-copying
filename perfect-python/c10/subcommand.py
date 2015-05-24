# -*- coding: utf-8 -*-
import sys
import argparse


def greeting(args):
    print("Hello, {name}!".format(name=args.name))


def goodbye(args):
    print("Goodbye, {name}!".format(name=args.name))


parser = argparse.ArgumentParser()
subparsers = parser.add_subparsers(dest='subparser_name')
subparser = subparsers.add_parser("greeting")
subparser.add_argument('-n', '--name', default='world')
subparser = subparsers.add_parser("goodbye")
subparser.add_argument('-n', '--name', default='world')
args = parser.parse_args()

if not args.subparser_name:
    parser.print_help()
    sys.exit(1)

if args.subparser_name == 'greeting':
    greeting(args)
elif args.subparser_name == 'goodbye':
    goodbye(args)
