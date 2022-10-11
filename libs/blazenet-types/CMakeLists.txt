####################################################################################################
# BlazeNet protocol types
#
# Defines an interface-only library that exports some headers for BlazeNet protocol types, from
# the MAC layer up.
####################################################################################################

add_library(blazenet-types INTERFACE)
target_include_directories(blazenet-types INTERFACE ${CMAKE_CURRENT_LIST_DIR}/Includes)

add_library(blazenet::types ALIAS blazenet-types)
