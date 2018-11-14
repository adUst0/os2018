#!/bin/bash

who | grep -v "$1" | grep -vc "$2"