/*
 * Note: this file originally auto-generated by mib2c using
 *        $
 */

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>
#include "ftsClkTrap.h"
#include "fts_scalar.h"

extern const oid snmptrap_oid[];
extern const size_t snmptrap_oid_len;
//int init_flag = 0;

void init_ftsClkTrap(void)
{
	//send_ftsClkTrap_trap();
	
    snmp_alarm_register(10,     /* seconds */
                        SA_REPEAT,      /* repeat (every 30 seconds). */
                        send_ftsClkTrap_trap,      /* our callback */
                        NULL    /* no callback data needed */
                        );
	//init_flag = 1;
}

void send_ftsClkTrap_trap(unsigned int clientreg,  void *clientarg)
{
    netsnmp_variable_list  *var_list = NULL;
    const oid ftsClkTrap_oid[] = { 1,3,6,1,4,1,63000,2,1,13,1,2,1,8,1 };
    const oid ftsClkMode_oid[] = { 1,3,6,1,4,1,63000,2,1,13,1,2,1,2,2, 0 };
    const oid ftsClkState_oid[] = { 1,3,6,1,4,1,63000,2,1,13,1,2,1,2,1, 0 };
	int var_ClkMode;
	int var_ClkState;
    /*
     * Set the snmpTrapOid.0 value
     */
    snmp_varlist_add_variable(&var_list,
        snmptrap_oid, snmptrap_oid_len,
        ASN_OBJECT_ID,
        ftsClkTrap_oid, sizeof(ftsClkTrap_oid));
    
    /*
     * Add any objects from the trap definition
     */
	var_ClkMode = (int)fts_scalar_getvar(VAR_FTS_CLK_MODE);
	var_ClkState = (int)fts_scalar_getvar(VAR_FTS_CLK_STATE);
    snmp_varlist_add_variable(&var_list,
        ftsClkMode_oid, OID_LENGTH(ftsClkMode_oid),
        ASN_INTEGER,
        /* Set an appropriate value for ftsClkMode */
        (void *)&var_ClkMode, sizeof(var_ClkMode));
    snmp_varlist_add_variable(&var_list,
        ftsClkState_oid, OID_LENGTH(ftsClkState_oid),
        ASN_INTEGER,
        /* Set an appropriate value for ftsClkState */
        (void *)&var_ClkState, sizeof(var_ClkState));

    /*
     * Add any extra (optional) objects here
     */

    /*
     * Send the trap to the list of configured destinations
     *  and clean up
     */
    send_v2trap( var_list );
    snmp_free_varbind( var_list );


    return SNMP_ERR_NOERROR;
}