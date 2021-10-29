execute_process(
        COMMAND git rev-parse HEAD
        OUTPUT_VARIABLE OUTPUT_GIT_COMMIT_HASH
        OUTPUT_STRIP_TRAILING_WHITESPACE
)
FILE(WRITE ${CMAKE_ARGV3}/git_info.h
"#ifndef GFXTK_GIT_COMMIT\n"
"#define GFXTK_GIT_COMMIT \"${OUTPUT_GIT_COMMIT_HASH}\"\n"
"#endif\n"
)