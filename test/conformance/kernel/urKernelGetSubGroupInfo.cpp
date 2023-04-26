// Copyright (C) 2023 Intel Corporation
// SPDX-License-Identifier: MIT

#include <uur/fixtures.h>

using urKernelGetSubGroupInfoTest =
    uur::urKernelTestWithParam<ur_kernel_sub_group_info_t>;

UUR_TEST_SUITE_P(
    urKernelGetSubGroupInfoTest,
    ::testing::Values(UR_KERNEL_SUB_GROUP_INFO_MAX_SUB_GROUP_SIZE,
                      UR_KERNEL_SUB_GROUP_INFO_MAX_NUM_SUB_GROUPS,
                      UR_KERNEL_SUB_GROUP_INFO_COMPILE_NUM_SUB_GROUPS,
                      UR_KERNEL_SUB_GROUP_INFO_SUB_GROUP_SIZE_INTEL),
    uur::deviceTestWithParamPrinter<ur_kernel_sub_group_info_t>);

TEST_P(urKernelGetSubGroupInfoTest, Success) {
    auto property_name = getParam();
    size_t property_size = 0;
    std::vector<char> property_value;
    ASSERT_SUCCESS(urKernelGetSubGroupInfo(kernel, device, property_name, 0,
                                           nullptr, &property_size));
    property_value.resize(property_size);
    ASSERT_SUCCESS(urKernelGetSubGroupInfo(kernel, device, property_name,
                                           property_size, property_value.data(),
                                           nullptr));
}

TEST_P(urKernelGetSubGroupInfoTest, InvalidNullHandleKernel) {
    uint32_t max_num_sub_groups = 0;
    ASSERT_EQ_RESULT(
        UR_RESULT_ERROR_INVALID_NULL_HANDLE,
        urKernelGetSubGroupInfo(
            nullptr, device, UR_KERNEL_SUB_GROUP_INFO_MAX_NUM_SUB_GROUPS,
            sizeof(max_num_sub_groups), &max_num_sub_groups, nullptr));
}

TEST_P(urKernelGetSubGroupInfoTest, InvalidNullHandleDevice) {
    uint32_t max_num_sub_groups = 0;
    ASSERT_EQ_RESULT(
        UR_RESULT_ERROR_INVALID_NULL_HANDLE,
        urKernelGetSubGroupInfo(
            kernel, nullptr, UR_KERNEL_SUB_GROUP_INFO_MAX_NUM_SUB_GROUPS,
            sizeof(max_num_sub_groups), &max_num_sub_groups, nullptr));
}

TEST_P(urKernelGetSubGroupInfoTest, InvalidEnumeration) {
    size_t bad_enum_length = 0;
    ASSERT_EQ_RESULT(UR_RESULT_ERROR_INVALID_ENUMERATION,
                     urKernelGetSubGroupInfo(
                         nullptr, device, UR_KERNEL_SUB_GROUP_INFO_FORCE_UINT32,
                         0, nullptr, &bad_enum_length));
}
