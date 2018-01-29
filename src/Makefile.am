include Makefile.include

AM_CPPFLAGS += -I$(builddir)

noinst_LIBRARIES = \
  libbolt_server.a \
  libbolt_common.a \
  libbolt_cli.a
if ENABLE_WALLET
noinst_LIBRARIES += libbolt_wallet.a
endif

bin_PROGRAMS =

if BUILD_BITCOIND
  bin_PROGRAMS += boltd
endif

if BUILD_BITCOIN_CLI
  bin_PROGRAMS += bolt-cli
endif

SUBDIRS = . $(BUILD_QT) $(BUILD_TEST)
DIST_SUBDIRS = . qt test
.PHONY: FORCE
# bolt core #
BITCOIN_CORE_H = \
  activemasternode.h \
  addrman.h \
  alert.h \
  allocators.h \
  base58.h \
  bignum.h \
  bloom.h \
  chainparams.h \
  checkpoints.h \
  checkqueue.h \
  clientversion.h \
  coincontrol.h \
  coins.h \
  compat.h \
  core.h \
  crypter.h \
  darksend.h \
  darksend-relay.h \
  db.h \
  hash.h \
  init.h \
  instantx.h \
  key.h \
  keepass.h \
  keystore.h \
  leveldbwrapper.h \
  limitedmap.h \
  main.h \
  masternode.h \
  masternode-pos.h \
  masternodeman.h \
  masternodeconfig.h \
  miner.h \
  mruset.h \
  netbase.h \
  net.h \
  noui.h \
  protocol.h \
  stealth.h \
  rpcclient.h \
  rpcprotocol.h \
  rpcserver.h \
  script.h \
  serialize.h \
  algorithm/sph_blake.h \
  sph_types.h \
  spork.h \
  sync.h \
  threadsafety.h \
  tinyformat.h \
  txdb.h \
  txmempool.h \
  ui_interface.h \
  uint256.h \
  util.h \
  version.h \
  walletdb.h \
  lz4/lz4.h \
  wallet.h

JSON_H = \
  json/json_spirit.h \
  json/json_spirit_error_position.h \
  json/json_spirit_reader.h \
  json/json_spirit_reader_template.h \
  json/json_spirit_stream_reader.h \
  json/json_spirit_utils.h \
  json/json_spirit_value.h \
  json/json_spirit_writer.h \
  json/json_spirit_writer_template.h

obj/build.h: FORCE
	@$(MKDIR_P) $(abs_top_builddir)/src/obj
	@$(top_srcdir)/share/genbuild.sh $(abs_top_builddir)/src/obj/build.h \
	  $(abs_top_srcdir)
version.o: obj/build.h

libbolt_server_a_SOURCES = \
  activemasternode.cpp \
  addrman.cpp \
  alert.cpp \
  bloom.cpp \
  checkpoints.cpp \
  coins.cpp \
  init.cpp \
  keystore.cpp \
  leveldbwrapper.cpp \
  main.cpp \
  miner.cpp \
  net.cpp \
  noui.cpp \
  rpcblockchain.cpp \
  rpcdarksend.cpp \
  rpcmining.cpp \
  rpcmisc.cpp \
  rpcnet.cpp \
  rpcrawtransaction.cpp \
  rpcserver.cpp \
  txdb.cpp \
  txmempool.cpp \
  $(JSON_H) \
  $(BITCOIN_CORE_H)

libbolt_wallet_a_SOURCES = \
  activemasternode.cpp \
  db.cpp \
  crypter.cpp \
  rpcdump.cpp \
  rpcwallet.cpp \
  stealth.cpp \
  wallet.cpp \
  walletdb.cpp \
  keepass.cpp \
  $(BITCOIN_CORE_H)

libbolt_common_a_SOURCES = \
  activemasternode.cpp \
  base58.cpp \
  allocators.cpp \
  chainparams.cpp \
  core.cpp \
  darksend.cpp \
  darksend-relay.cpp \
  masternode.cpp \
  masternode-pos.cpp \
  masternodeman.cpp \
  masternodeconfig.cpp \
  instantx.cpp \
  hash.cpp \
  key.cpp \
  netbase.cpp \
  protocol.cpp \
  rpcprotocol.cpp \
  script.cpp \
  sync.cpp \
  util.cpp \
  version.cpp \
  spork.cpp \
  algorithm/blake.c \
  lz4/lz4.c \
  $(BITCOIN_CORE_H)

if GLIBC_BACK_COMPAT
libbolt_common_a_SOURCES += compat/glibc_compat.cpp
libbolt_common_a_SOURCES += compat/glibcxx_compat.cpp
endif

libbolt_cli_a_SOURCES = \
  rpcclient.cpp \
  $(BITCOIN_CORE_H)

nodist_libbolt_common_a_SOURCES = $(top_srcdir)/src/obj/build.h
#

# boltd binary #
boltd_LDADD = \
  libbolt_server.a \
  libbolt_cli.a \
  libbolt_common.a \
  $(LIBLEVELDB) \
  $(LIBMEMENV)
if ENABLE_WALLET
boltd_LDADD += libbolt_wallet.a
endif
boltd_SOURCES = bolt.cpp
#

if TARGET_WINDOWS
boltd_SOURCES += boltd-res.rc
endif

AM_CPPFLAGS += $(BDB_CPPFLAGS)
boltd_LDADD += $(BOOST_LIBS) $(BDB_LIBS)

# bolt-cli binary #
bolt_cli_LDADD = \
  libbolt_cli.a \
  libbolt_common.a \
  $(BOOST_LIBS)
bolt_cli_SOURCES = bolt-cli.cpp
#

if TARGET_WINDOWS
bolt_cli_SOURCES += bolt-cli-res.rc
endif

# NOTE: This dependency is not strictly necessary, but without it make may try to build both in parallel, which breaks the LevelDB build system in a race
leveldb/libleveldb.a: leveldb/libmemenv.a

leveldb/%.a:
	@echo "Building LevelDB ..." && $(MAKE) -C $(@D) $(@F) CXX="$(CXX)" \
	  CC="$(CC)" PLATFORM=$(TARGET_OS) AR="$(AR)" $(LEVELDB_TARGET_FLAGS) \
	  OPT="$(CXXFLAGS) $(CPPFLAGS)"

qt/boltstrings.cpp: $(libbolt_server_a_SOURCES) $(libbolt_common_a_SOURCES) $(libbolt_cli_a_SOURCES)
	@test -n $(XGETTEXT) || echo "xgettext is required for updating translations"
	@cd $(top_srcdir); XGETTEXT=$(XGETTEXT) share/qt/extract_strings_qt.py

CLEANFILES = leveldb/libleveldb.a leveldb/libmemenv.a *.gcda *.gcno

DISTCLEANFILES = obj/build.h

EXTRA_DIST = leveldb Makefile.include

clean-local:
	-$(MAKE) -C leveldb clean
	rm -f leveldb/*/*.gcno leveldb/helpers/memenv/*.gcno
