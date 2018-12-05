#!/bin/bash

rm -f $IAS_TEST_DS_LMDB/*
mkdir -p $IAS_TEST_DS_LMDB

lmdb_dump  $IAS_TEST_DS_LMDB