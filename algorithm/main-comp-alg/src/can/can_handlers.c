#include <byteswap.h>
#include "vs_can_api.h"
#include "can_handlers.h"
#include "can_master.h"



/* This function updates state machine's CAN_Data with:
 *     Pack State of Charge
 *     Pack Voltage
 *     Pack Current
 *
 * Params:
 *     VSCAN_MSG *msg -> pointer to received CAN message frame
 *     CAN_Data *data -> pointer to CAN_data struct used by state machine
 *
 * Returns:
 *     void
 */
void bms_pack_handler(VSCAN_MSG *msg, CAN_Data *data) {
    unsigned short pack_soc     = *((unsigned short *) (&(msg->Data[0])));
    unsigned short pack_voltage = *((unsigned short *) (&(msg->Data[2])));
    unsigned short pack_current = *((unsigned short *) (&(msg->Data[4])));
    
    STORE(data->pack_soc, pack_soc);
    STORE(data->pack_voltage, pack_voltage);
    STORE(data->pack_current, pack_current);
}


/* This function updates state machine's CAN_Data with:
 *     Minimum voltage
 *     Maximum Voltage
 *     Average Temperature
 *     Highest Temperature
 *
 * Params:
 *     VSCAN_MSG *msg -> pointer to received CAN message frame
 *     CAN_Data *data -> pointer to CAN_data struct used by state machine
 *
 * Returns:
 *     void
 */
void bms_other_handler(VSCAN_MSG *msg, CAN_Data *data){
    unsigned short min_voltage = *((unsigned short *) (&(msg->Data[0])));
    unsigned short max_voltage = *((unsigned short *) (&(msg->Data[2])));
    unsigned short avg_temp = *((unsigned short *) (&(msg->Data[4])));
    unsigned short high_temp = *((unsigned short *) (&(msg->Data[6])));

    STORE(data->min_voltage, min_voltage);
    STORE(data->max_voltage, max_voltage);
    STORE(data->avg_temp, avg_temp);
    STORE(data->high_temp, high_temp);

}



/* This function updates state machine's CAN_Data with:
 *     Failsafe Status
 *     DTC Flags #1
 *     DTC Flags #2
 *     Rolling Counter
 *
 * Params:
 *     VSCAN_MSG *msg -> pointer to received CAN message frame
 *     CAN_Data *data -> pointer to CAN_data struct used by state machine
 *
 * Returns:
 *     void
 */
void bms_error_handler(VSCAN_MSG *msg, CAN_Data *data){
    unsigned char failsafe_status = *((unsigned char *) (&(msg->Data[0])));
    unsigned char dtc_flags_1 = *((unsigned char *) (&(msg->Data[1])));
    unsigned short dtc_flags_2 = *((unsigned short *) (&(msg->Data[2])));
    unsigned short rolling_counter = *((unsigned short *) (&(msg->Data[4])));

    STORE(data->failsafe_status, failsafe_status);
    STORE(data->dtc_flags_1, dtc_flags_1);
    STORE(data->dtc_flags_2, dtc_flags_2);
    STORE(data->rolling_counter, rolling_counter);

}




/* This function updates state machine's CAN_Data with:
 *     Status Flags
 *     Electrical Isolation (ohm/vol);
 *     Electrical Isolation Uncertainty
 *     Energy Stored
 *     Energy Stored Uncertainty
 *
 * Params:
 *     VSCAN_MSG *msg -> pointer to received CAN message frame
 *     CAN_Data *data -> pointer to CAN_data struct used by state machine
 *
 * Returns:
 *     void
 */
void iso_state_handler(VSCAN_MSG *msg, CAN_Data *data){
    unsigned char status_flags = *((unsigned char *) (&(msg->Data[1])));
    unsigned short electrical_isolation = *((unsigned short *) (&(msg->Data[2])));
    unsigned char electrical_isolation_uncert = *((unsigned char *) (&(msg->Data[4])));
    unsigned short energy_stored = *((unsigned short *) (&(msg->Data[5])));
    unsigned char energy_stored_uncert = *((unsigned char *) (&(msg->Data[7])));

    STORE(data->iso_error_flags, status_flags);
    STORE(data->electrical_isolation, bswap_16(electrical_isolation));
    STORE(data->electrical_isolation_uncert, electrical_isolation_uncert);
    STORE(data->energy_stored, bswap_16(energy_stored));
    STORE(data->energy_stored_uncert, energy_stored_uncert);

}




/* This function updates state machine's CAN_Data with:
 *     status flags
 *     rp Isolation resistance
 *     rp Isolation resistance uncertainty
 *     rn Isolation resistance
 *     rn Isolation resistance uncertainty
 *
 * Params:
 *     VSCAN_MSG *msg -> pointer to received CAN message frame
 *     CAN_Data *data -> pointer to CAN_data struct used by state machine
 *
 * Returns:
 *     void
 */
void iso_resistance_handler(VSCAN_MSG *msg, CAN_Data *data){
    unsigned char status_flags = *((unsigned char *) (&(msg->Data[1])));
    unsigned short rp_iso_resistance = *((unsigned short *) (&(msg->Data[2])));
    unsigned char rp_iso_resistance_uncert = *((unsigned char *) (&(msg->Data[4])));
    unsigned short rn_iso_resistance = *((unsigned short *) (&(msg->Data[5])));
    unsigned char rn_iso_resistance_uncert = *((unsigned char *) (&(msg->Data[7])));

    STORE(data->iso_error_flags, status_flags);
    STORE(data->rp_iso_resistance, bswap_16(rp_iso_resistance));
    STORE(data->rp_iso_resistance_uncert, rp_iso_resistance_uncert);
    STORE(data->rn_iso_resistance, bswap_16(rn_iso_resistance));
    STORE(data->rn_iso_resistance_uncert, rn_iso_resistance_uncert);
}




/* This function updates state machine's CAN_Data with:
 *     Pack Status Flags
 *     Pack error flags
 *
 * Params:
 *     VSCAN_MSG *msg -> pointer to received CAN message frame
 *     CAN_Data *data -> pointer to CAN_data struct used by state machine
 *
 * Returns:
 *     void
 */
void iso_error_handler(VSCAN_MSG *msg, CAN_Data *data){
    unsigned char status_flags = *((unsigned char *) (&(msg->Data[1])));
    unsigned char error_flags = *((unsigned char *) (&(msg->Data[2])));
    
    STORE(data->iso_error_flags, status_flags);
    STORE(data->iso_error_flags, error_flags);

}




/* This function updates state machine's CAN_Data with:
 *     Pack status flags
 *     Pack battery voltage
 *     Pack battery voltage uncertainty
 *     Pack Max battery voltage
 *     Pack max battery voltage uncertainty
 *
 * Params:
 *     VSCAN_MSG *msg -> pointer to received CAN message frame
 *     CAN_Data *data -> pointer to CAN_data struct used by state machine
 *
 * Returns:
 *     void
 */
void lipo_handler(VSCAN_MSG *msg, CAN_Data *data){
    unsigned char status_flags = *((unsigned char *) (&(msg->Data[1])));
    unsigned short battery_volt = bswap_16(*((short *) (&(msg->Data[2]))));
    unsigned char battery_volt_uncert = *((char *) (&(msg->Data[4])));
    unsigned short max_battery_volt = bswap_16(*((short *) (&(msg->Data[5]))));
    unsigned char max_battery_volt_uncert = *((char *) (&(msg->Data[7])));
    
    STORE(data->iso_status_flags, status_flags);
    STORE(data->battery_volt, battery_volt);
    STORE(data->battery_volt_uncert, battery_volt_uncert);
    STORE(data->max_battery_volt, max_battery_volt);
    STORE(data->max_battery_volt_uncert, max_battery_volt_uncert);
    
    if (max_battery_volt > 400) {
        STORE(data->iso_status_flags_left, status_flags);
        STORE(data->battery_volt_left, battery_volt);
        STORE(data->battery_volt_uncert_left, battery_volt_uncert);
        STORE(data->max_battery_volt_left, max_battery_volt);
        STORE(data->max_battery_volt_uncert_left, max_battery_volt_uncert);
    } else {
        STORE(data->iso_status_flags_right, status_flags);
        STORE(data->battery_volt_right, battery_volt);
        STORE(data->battery_volt_uncert_right, battery_volt_uncert);
        STORE(data->max_battery_volt_right, max_battery_volt);
        STORE(data->max_battery_volt_uncert_right, max_battery_volt_uncert);
    }
}

/* This function updates state machine's CAN_Data with:
 * None
 * Params:
 *     VSCAN_MSG *msg -> pointer to received CAN message frame
 *     CAN_Data *data -> pointer to CAN_data struct used by state machine
 *
 * Returns:
 *     void
 */
void ready_to_transmit_handler(VSCAN_MSG *msg, CAN_Data *data){
    
}

/* This function updates state machine's CAN_Data with:
 * None
 * Params:
 *     VSCAN_MSG *msg -> pointer to received CAN message frame
 *     CAN_Data *data -> pointer to CAN_data struct used by state machine
 *
 * Returns:
 *     void
 */
void transmit_enable_handler(VSCAN_MSG *msg, CAN_Data *data){
    
}


/* This function updates state machine's CAN_Data with:
 *     Pack max speed
 *
 * Params:
 *     VSCAN_MSG *msg -> pointer to received CAN message frame
 *     CAN_Data *data -> pointer to CAN_data struct used by state machine
 *
 * Returns:
 *     void
 */
void max_speed_handler(VSCAN_MSG *msg, CAN_Data *data){
    short max_speed = *((short *) (&(msg->Data[1])));
    STORE(data->max_speed, max_speed);

}




/* This function updates state machine's CAN_Data with:
 *     Pack device current
 *
 * Params:
 *     VSCAN_MSG *msg -> pointer to received CAN message frame
 *     CAN_Data *data -> pointer to CAN_data struct used by state machine
 *
 * Returns:
 *     void
 */
void device_current_handler(VSCAN_MSG *msg, CAN_Data *data){
   short dev_current = *((short *) (&(msg->Data[1])));
   STORE(data->dev_current, dev_current);
}





/* This function updates state machine's CAN_Data with:
 *     Current 200pc
 *
 * Params:
 *     VSCAN_MSG *msg -> pointer to received CAN message frame
 *     CAN_Data *data -> pointer to CAN_data struct used by state machine
 *
 * Returns:
 *     void
 */
void current_200pc_handler(VSCAN_MSG *msg, CAN_Data *data){
   short current_200pc = *((short *) (&(msg->Data[1])));
   STORE(data->current_200pc, current_200pc);

}




/* This function updates state machine's CAN_Data with:
 *     Percent Max Spered
 *
 * Params:
 *     VSCAN_MSG *msg -> pointer to received CAN message frame
 *     CAN_Data *data -> pointer to CAN_data struct used by state machine
 *
 * Returns:
 *     void
 */
void actual_speed_handler(VSCAN_MSG *msg, CAN_Data *data){
    short percent_max_speed = *((short *) (&(msg->Data[1])));
    STORE(data->percent_max_speed, percent_max_speed);

}




/* This function updates state machine's CAN_Data with:
 *     True current
 *
 * Params:
 *     VSCAN_MSG *msg -> pointer to received CAN message frame
 *     CAN_Data *data -> pointer to CAN_data struct used by state machine
 *
 * Returns:
 *     void
 */
void actual_current_handler(VSCAN_MSG *msg, CAN_Data *data){
   short true_current = *((short *) (&(msg->Data[1])));
   STORE(data->true_current, true_current);
}





/* This function updates state machine's CAN_Data with:
 *     Revolutions
 *
 * Params:
 *     VSCAN_MSG *msg -> pointer to received CAN message frame
 *     CAN_Data *data -> pointer to CAN_data struct used by state machine
 *
 * Returns:
 *     void
 */
void actual_position_handler(VSCAN_MSG *msg, CAN_Data *data){
    int revolutions = *((int *) (&(msg->Data[1])));
    STORE(data->revolutions, revolutions);
}

/* This function updates state machine's CAN_Data with:
 *     controller_bus_voltage
 *
 * Params:
 *     VSCAN_MSG *msg -> pointer to received CAN message frame
 *     CAN_Data *data -> pointer to CAN_data struct used by state machine
 *
 * Returns:
 *     void
 */
void controller_volt_handler(VSCAN_MSG *msg, CAN_Data *data) {
    unsigned short controller_bus_voltage = *((unsigned short *) (&(msg->Data[1])));
    STORE(data->controller_bus_voltage, controller_bus_voltage);
}

/* This function updates state machine's CAN_Data with:
 *     controller_errors
 *
 * Params:
 *     VSCAN_MSG *msg -> pointer to received CAN message frame
 *     CAN_Data *data -> pointer to CAN_data struct used by state machine
 *
 * Returns:
 *     void
 */
void controller_errors_handler(VSCAN_MSG *msg, CAN_Data *data) {
    unsigned int controller_errors = *((unsigned int *) (&(msg->Data[1])));
    STORE(data->controller_errors, controller_errors);
}

/* This function updates state machine's CAN_Data with:
 *     controller_errors
 *
 * Params:
 *     VSCAN_MSG *msg -> pointer to received CAN message frame
 *     CAN_Data *data -> pointer to CAN_data struct used by state machine
 *
 * Returns:
 *     void
 */
void controller_status_handler(VSCAN_MSG *msg, CAN_Data *data) {
    unsigned short controller_status = *((unsigned short *) (&(msg->Data[1])));
    STORE(data->controller_status, controller_status);
}

