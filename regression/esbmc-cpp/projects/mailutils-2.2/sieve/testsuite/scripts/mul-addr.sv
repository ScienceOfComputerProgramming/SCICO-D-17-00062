# -*- sieve -*-
# This file is part of Mailutils testsuite.
# Copyright (C) 2002, 2010 Free Software Foundation, Inc.
# See file COPYING for distribution conditions.

require "fileinto";

if address :localpart :is ["To", "Cc"] [ "foo", "oof" ]
  {
    discard;
  } 