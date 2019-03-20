cc_library(
    name = "grpc",
    srcs = ["libgrpc.so","libgrpc++.so"],
    hdrs = glob(["include/**/*.h"]),
)

cc_import(
  name = "protobuf",
  static_library = "libprotobuf.a",
)

cc_import(
  name = "mysqlclient",
  hdrs = glob(["include/mysql/**/*.h"]),
  static_library = "libmysqlclient.a",
)

cc_import(
  name = "libz",
  static_library = "libz.a",
)

cc_import(
  name = "hiredis",
  hdrs = glob(["include/redis/**/*.h"]),
  static_library = "libhiredis.a",
)

cc_binary(
    name = "miaosha_server",
    srcs = ["miaosha_server.cpp"],
    deps = [":CMiaoshaServer"],
    copts = ["-Isrc/include"],
    linkopts = ["-lpthread", "-ldl"],
    linkstatic = 1,
)

cc_library(
    name = "CMiaoshaServer",
    srcs = ["CMiaoshaServer.cpp"],
    hdrs = ["CMiaoshaServer.h"],
    deps = [":CMiaoshaWorker"],
    copts = ["-Isrc/include"],
)

cc_library(
    name = "CMiaoshaWorker",
    srcs = ["CMiaoshaWorker.cpp"],
    hdrs = ["CMiaoshaWorker.h","comm_def.h"],
    deps = [
      ":miaosha.pb",
      ":miaosha.grpc.pb",
      ":CMysqlPoolMgr",
      ":CRedisPoolMgr",
      ":grpc",
      ":protobuf"],
    copts = ["-Isrc/include"],
)

cc_binary(
    name = "miaosha_client",
    srcs = ["miaosha_client.cpp"],
    deps = [":CMiaoshaClient"],
    copts = ["-Isrc/include"],
    linkopts = ["-lpthread", "-ldl"],
    linkstatic = 1,
)

cc_library(
    name = "CMiaoshaClient",
    srcs = ["CMiaoshaClient.cpp"],
    hdrs = ["CMiaoshaClient.h","comm_def.h"],
    deps = [
      ":miaosha.pb",
      ":miaosha.grpc.pb",
      ":CThread",
      ":grpc",
      ":protobuf"
      ],
    copts = ["-Isrc/include"],
)

cc_library(
    name = "miaosha.pb",
    srcs = ["miaosha.pb.cc"],
    hdrs = ["miaosha.pb.h"],
    copts = ["-Isrc/include"],
)

cc_library(
    name = "miaosha.grpc.pb",
    srcs = ["miaosha.grpc.pb.cc"],
    hdrs = ["miaosha.grpc.pb.h","miaosha.pb.h"],
    copts = ["-Isrc/include"],
)

cc_library(
    name = "CMysqlPoolMgr",
    srcs = ["CMysqlPoolMgr.cpp"],
    hdrs = ["CMysqlPoolMgr.h"],
    deps = [
      ":mysqlclient",
      ":CThread",
      ":libz"],
    copts = ["-Isrc/include"],
)

cc_library(
    name = "CRedisPoolMgr",
    srcs = ["CRedisPoolMgr.cpp"],
    hdrs = ["CRedisPoolMgr.h"],
    deps = [
      ":hiredis",
      ":CThread"],
    copts = ["-Isrc/include"],
)

cc_library(
    name = "CThread",
    srcs = ["CThread.cpp"],
    hdrs = ["CThread.h"],
)
