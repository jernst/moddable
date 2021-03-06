/*
 * Copyright (c) 2019  Moddable Tech, Inc.
 *
 *   This file is part of the Moddable SDK Runtime.
 *
 *   The Moddable SDK Runtime is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU Lesser General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   The Moddable SDK Runtime is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU Lesser General Public License for more details.
 *
 *   You should have received a copy of the GNU Lesser General Public License
 *   along with the Moddable SDK Runtime.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

/*
	Analog - uing ESP8266
*/

#include "user_interface.h"	// esp8266 functions

#include "xsmc.h"			// xs bindings for microcontroller
#ifdef __ets__
	#include "xsHost.h"		// esp platform support
#else
	#error - unsupported platform
#endif
#include "mc.xs.h"			// for xsID_* values

static uint8_t gInUse;

void xs_analog_constructor(xsMachine *the)
{
	if (gInUse)
		xsUnknownError("in use");

	gInUse = 1;
}

void xs_analog_destructor(void *data)
{
	gInUse = 0;
}

void xs_analog_close(xsMachine *the)
{
	xs_analog_destructor(NULL);
}

void xs_analog_read(xsMachine *the)
{
	int value = system_adc_read();
	xsmcSetInteger(xsResult, (value > 1023) ? 1023 : value);		// pin, as API returns 1024.
}

/*
	Normatively define values returned so that they are consistent across microcontrollers from various vendors
*/
