
#####################################################
# Constants #########################################
#####################################################

GLFW_VERSION = "3.3.5"
GLM_VERSION = "0.9.9.8"

#####################################################
# Google ############################################
#####################################################

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

# Google Test
http_archive(
  name = "com_google_googletest",
  urls = ["https://github.com/google/googletest/archive/5ab508a01f9eb089207ee87fd547d290da39d015.zip"],
  strip_prefix = "googletest-5ab508a01f9eb089207ee87fd547d290da39d015",
)

# GLOG
http_archive(
    name = "com_github_gflags_gflags",
    sha256 = "34af2f15cf7367513b352bdcd2493ab14ce43692d2dcd9dfc499492966c64dcf",
    strip_prefix = "gflags-2.2.2",
    urls = ["https://github.com/gflags/gflags/archive/v2.2.2.tar.gz"],
)

http_archive(
    name = "com_github_google_glog",
    sha256 = "122fb6b712808ef43fbf80f75c52a21c9760683dae470154f02bddfc61135022",
    strip_prefix = "glog-0.6.0",
    urls = ["https://github.com/google/glog/archive/v0.6.0.zip"],
)

#####################################################
# Vulkan ############################################
#####################################################

load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

git_repository(
    name = "rules_vulkan",
    remote = "https://github.com/jadarve/rules_vulkan.git",
    tag = "v0.0.6"
)

load("@rules_vulkan//vulkan:repositories.bzl", "vulkan_repositories")

vulkan_repositories()

#####################################################
# Third-Party #######################################
#####################################################


http_archive(
    name = "glfw",
    build_file = "@//third-party/glfw:glfw.BUILD",
    sha256 = "a89bb6074bc12bc12fcd322dcf848af81b679ccdc695f70b29ca8a9aa066684b",
    strip_prefix = "glfw-{}".format(GLFW_VERSION),
    urls = ["https://github.com/glfw/glfw/archive/{}.zip".format(GLFW_VERSION)],
)


http_archive(
    name = "glm",
    build_file = "@//third-party/glm:glm.BUILD",
    sha256 = "4605259c22feadf35388c027f07b345ad3aa3b12631a5a316347f7566c6f1839",
    strip_prefix = "glm-{}".format(GLM_VERSION),
    urls = ["https://github.com/g-truc/glm/archive/{}.zip".format(GLM_VERSION)],
)

git_repository(
    name = "mathfu",
    commit = "da23a1227bb65fbb7f2f5b6c504fbbdd1dfdab4b",
    remote = "https://github.com/google/mathfu.git",
)