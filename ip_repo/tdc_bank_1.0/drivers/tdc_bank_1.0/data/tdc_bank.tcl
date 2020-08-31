#uses "xillib.tcl"

proc generate {drv_handle} {
    ::hsi::utils::define_include_file $drv_handle "xparameters.h" "XTDC" "NUM_INSTANCES" "DEVICE_ID" "C_S_AXI_BASEADDR" "C_S_AXI_HIGHADDR" "sampling_len_g" "count_tdc_g"
    ::hsi::utils::define_config_file $drv_handle "xtdc_g.c" "XTDC" "DEVICE_ID" "C_S_AXI_BASEADDR" "sampling_len_g" "count_tdc_g"
    ::hsi::utils::define_canonical_xpars $drv_handle "xparameters.h" "XTDC" "NUM_INSTANCES" "DEVICE_ID" "C_S_AXI_BASEADDR" "C_S_AXI_HIGHADDR" "sampling_len_g" "count_tdc_g"
}
