#include <utils/Log.h>
#include <hardware/hardware.h>
#include <hardware/hwcomposer.h>

static hw_module_t *real_module;
static hw_device_t *real_device;
static hwc_composer_device_1_t *hwc;
extern int load_real_hwc(char * path, hw_module_t **pHmi);
extern int open_real_hwc(hw_module_t *module, hw_device_t **real_device);


void test_getDisplayAttributes() {
    uint32_t config = 0;
    size_t numConfigs;
    int ret;
    int32_t values[6];
    static const uint32_t DISPLAY_ATTRIBUTES[] = {
        HWC_DISPLAY_VSYNC_PERIOD,
        HWC_DISPLAY_WIDTH,
        HWC_DISPLAY_HEIGHT,
        HWC_DISPLAY_DPI_X,
        HWC_DISPLAY_DPI_Y,
        HWC_DISPLAY_NO_ATTRIBUTE,
    };


    ret = hwc->getDisplayAttributes(hwc,0,config,DISPLAY_ATTRIBUTES, values);
    printf("getDisplayAttributes: ret =%d vsync_period=%d w=%d h=%d dpix=%d dpiy=%d\n",ret,values[0],values[1],values[2],values[3],values[4]);
}

void test_getDisplayConfigs() {
    uint32_t configs;
    size_t numConfigs;
    int ret;
    ret = hwc->getDisplayConfigs(hwc,1,&configs,&numConfigs);
    printf("getDisplayConfigs: ret =%d configs=%d numConfigs=%d\n",ret,configs,numConfigs);
}


int main(void) {
load_real_hwc("/system/lib64/hw/hwcomposer.hi6250.so.bak", &real_module);
if(!open_real_hwc(real_module,&real_device)) {
    printf("HWC open\n");
    hwc = (hwc_composer_device_1_t *)real_device;
    test_getDisplayConfigs();
    test_getDisplayAttributes();
}
return 0;
}

