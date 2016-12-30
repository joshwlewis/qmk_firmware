/* Copyright 2016 Fred Sundvik
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef QUANTUM_APIV2_API_RESPONSES_H_
#define QUANTUM_APIV2_API_RESPONSES_H_

// See api_requests.h for documentation of how to add new responses

typedef struct __attribute((packed, aligned(4))) {
    uint8_t successful;
} res_connect;


#endif /* QUANTUM_APIV2_API_RESPONSES_H_ */
