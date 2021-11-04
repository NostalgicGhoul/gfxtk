add_custom_target(gfxtk_git_info)
add_custom_command(TARGET gfxtk_git_info
        COMMAND ${CMAKE_COMMAND} -P ${GFXTK_SOURCE_DIR}/cmake/GenerateGitInfoHeader.cmake "${GFXTK_SOURCE_DIR}/.git" "${GFXTK_GIT_INFO_HEADER_PATH}"
)