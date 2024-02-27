#include "i2c_scanner.hpp"

#include <iostream>
#include <iomanip>

/**
 * @brief Check if an I2C device is present at a given address.
 *
 * This function checks if an I2C device is present at the specified address by attempting to write
 * a byte to the device. It uses the i2c_device_present helper function for the check.
 *
 * @param i2c The I2C instance.
 * @param addr The I2C address to check.
 * @param d Vector to store the addresses of the detected devices.
 * @return The number of detected devices.
 */
int scan_i2c(i2c_inst_t *i2c, std::vector<uint8_t> &d)
{
    // Iterate through all possible I2C addresses (7-bit)
    for (int addr = 0; addr < (1 << 7); ++addr)
    {
        // Check if an I2C device is present at the current address
        if (i2c_device_present(i2c, addr, 10000))
            d.push_back(addr);
    }
    return d.size();
}

/**
 * @brief Check if an I2C address is reserved.
 *
 * This function checks if an I2C address is reserved by examining the high bits of the address.
 * Reserved addresses are those where the 7-bit address ends with '000' or '111'.
 *
 * @param addr The I2C address to check.
 * @return true if the address is reserved, false otherwise.
 */
static bool i2c_reserved_addr(const uint8_t &addr)
{
    return (addr & 0x78) == 0 || (addr & 0x78) == 0x78;
}

/**
 * @brief Check if an I2C device is present at a given address with timeout.
 *
 * This function checks if an I2C device is present at the specified address by attempting to write
 * a byte to the device with a timeout. It returns true if the write is successful, indicating
 * the device is present; otherwise, it returns false.
 *
 * @param i2c The I2C instance.
 * @param addr The I2C address to check.
 * @param tmo Timeout value in microseconds.
 * @return true if the device is present, false otherwise.
 */
bool i2c_device_present(i2c_inst_t *i2c, const uint8_t addr, const uint tmo)
{
    // std::cout << __FILE__ << " " << __FUNCTION__ << " " << std::hex << "addr: " << (int)addr << std::endl;
    int ret;
    uint8_t txdata = 0;

    // Check if the address is reserved (commented out for now)
    // if (i2c_reserved_addr(addr))
    //     ret = PICO_ERROR_GENERIC;
    // else
    ret = i2c_write_timeout_us(i2c, addr, &txdata, 1, false, tmo);
    // std::cout << __FILE__ << " " << __FUNCTION__ << " " << std::hex << "ret: " << ret << std::dec << " tmo: " << tmo << std::endl;

    return (ret >= 0);
}
