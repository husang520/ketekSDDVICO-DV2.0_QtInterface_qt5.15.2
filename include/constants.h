#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "types.h"

/**
 * The default size of an event scope in bytes, typically retrieved using the function #getEventScope().
 */
const UInt16Type EVENT_SCOPE_SIZE = 8192;

/**
 * The default size of an "all parameters"-array in bytes, typically retrieved using the function #getAllParameters().
 */
const UInt16Type ALL_PARAMETERS_SIZE = 1024;

/**
 * The size of a firmware section, typically used by the function #writeFirmwareSection().
 */
const UInt16Type FIRMWARE_SECTION_SIZE = 1024;

#endif // CONSTANTS_H
