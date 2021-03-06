#
# $PostgreSQL: pgsql/contrib/pgcrypto/Makefile,v 1.12 2004/09/14 03:39:48 tgl Exp $
#

# either 'builtin', 'mhash', 'openssl'
cryptolib = builtin

# either 'builtin', 'system'
cryptsrc = builtin

# Random source, preferred order:
# 'dev'      - read from random device
#
# 'openssl'  - use openssl PRNG.
#              Note that currently pgcrypto does not do any
#              entropy feeding to it
#              This works ofcouse only with cryptolib = openssl
#
# 'silly'    - use libc random() - very weak
random = silly
random_dev = \"/dev/urandom\"

##########################

ifeq ($(cryptolib), builtin)
CRYPTO_CFLAGS =
CRYPTO_LDFLAGS =
SRCS = md5.c sha1.c internal.c blf.c rijndael.c
endif

ifeq ($(cryptolib), openssl)
CRYPTO_CFLAGS = -I/usr/include/openssl
CRYPTO_LDFLAGS = -lcrypto
SRCS = openssl.c
endif

ifeq ($(cryptolib), mhash)
CRYPTO_CFLAGS = -I/usr/local/include
CRYPTO_LDFLAGS = -L/usr/local/lib -lmcrypt -lmhash -lltdl
SRCS = mhash.c
endif

ifeq ($(cryptsrc), builtin)
SRCS += crypt-blowfish.c crypt-des.c crypt-md5.c 
else
CRYPTO_CFLAGS += -DPX_SYSTEM_CRYPT
endif

ifeq ($(random), dev)
CRYPTO_CFLAGS += -DRAND_DEV=$(random_dev)
endif
ifeq ($(random), openssl)
CRYPTO_CFLAGS += -DRAND_OPENSSL
endif
ifeq ($(random), silly)
CRYPTO_CFLAGS += -DRAND_SILLY
endif

SRCS		+= pgcrypto.c px.c px-hmac.c px-crypt.c misc.c \
			crypt-gensalt.c random.c

MODULE_big	= pgcrypto
OBJS		= $(SRCS:.c=.o)
DOCS		= README.pgcrypto
DATA_built	= pgcrypto.sql
EXTRA_CLEAN	= gen-rtab

PG_CPPFLAGS	= $(CRYPTO_CFLAGS) -I$(srcdir) 
SHLIB_LINK 	= $(CRYPTO_LDFLAGS)

REGRESS = init md5 sha1 hmac-md5 hmac-sha1 blowfish rijndael \
		crypt-des crypt-md5 crypt-blowfish crypt-xdes 


ifdef USE_PGXS
PGXS = $(shell pg_config --pgxs)
include $(PGXS)
else
subdir = contrib/pgcrypto
top_builddir = ../..
include $(top_builddir)/src/Makefile.global
include $(top_srcdir)/contrib/contrib-global.mk
endif

# to make ws2_32.lib the last library (must occur after definition of PORTNAME)
ifeq ($(PORTNAME),win32)
SHLIB_LINK += -lwsock32 -lws2_32
endif


rijndael.o: rijndael.tbl

rijndael.tbl:
	$(CC) $(CPPFLAGS) $(CFLAGS) -DPRINT_TABS rijndael.c -o gen-rtab
	./gen-rtab > rijndael.tbl
