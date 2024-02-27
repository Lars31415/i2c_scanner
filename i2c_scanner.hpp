/**
 * @file i2c_scanner.hpp
 * @brief This file contains the declaration of the I2C scanner functions.
 */

#ifndef I2C_SCANNER_HPP
#define I2C_SCANNER_HPP

#include <vector>
#include <hardware/i2c.h>

/**
 * @brief Check if an I2C device is present on the bus.
 *
 * @param i2c The I2C instance to use.
 * @param addr The I2C address of the device.
 * @param tmo The timeout in microseconds.
 * @return true The device is present.
 * @return false The device is not present.
 */
bool i2c_device_present(i2c_inst_t *i2c, const uint8_t addr, const uint tmo = 100000);

/**
 * @brief Scan the I2C bus for devices.
 *
 * @param i2c The I2C instance to use.
 * @param d A vector to store the detected device addresses.
 * @return int The number of devices detected.
 */
int scan_i2c(i2c_inst_t *i2c, std::vector<uint8_t> &d);

#endif // I2C_SCANNER_HPP