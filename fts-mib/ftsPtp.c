/*
 * Note: this file originally auto-generated by mib2c using
 *  $
 */

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>
#include "ftsPtpTable.h"
#include "ftsCan.h"
#include "can.h"





#include <stdio.h>
#include <string.h>
#include <stdlib.h>
	
	
#include "fts_cfg.h"


#if 0
/* Typical data structure for a row entry */
struct ftsPtpTable_entry {
    /* Index values */
    long ftsPtpIndex;

    /* Column values */
   // long ftsPtpIndex;
    long ftsPtpState;
    long ftsPtpDomain;
    long old_ftsPtpDomain;
    long ftsPtpDelayReqs;
    long ftsPtpDelayResps;

    int   valid;
};
#endif

/* Typical data structure for a row entry */
struct ftsPtpTable_entry {
    /* Index values */
    long ftsPtpSlot;
    /* Column values */
   // long ftsPtpIndex;
    long ftsPtpError;
    long ftsPtpMode;
	long ftsPtpSynRate;
	long ftsPtpDelayRate;

    int   valid;
};

struct ptp_board_s{
	int num;
	int slot[3]; //
	int error[3]; //board is ok
} ptp_board;  //delete 

/** Initializes the ftsRefTable module */

/* create a new row in the table */
netsnmp_tdata_row *
ftsPtpTable_createEntry(netsnmp_tdata *table_data
                 , long  ftsPtpSlot, long  ftsPtpError, long  ftsPtpMode, long  ftsPtpSynRate, long ftsPtpDelayRate) {


    struct ftsPtpTable_entry *entry;
    netsnmp_tdata_row *row;

    entry = SNMP_MALLOC_TYPEDEF(struct ftsPtpTable_entry);
    if (!entry)
        return NULL;

    row = netsnmp_tdata_create_row();
    if (!row) {
        SNMP_FREE(entry);
        return NULL;
    }
    row->data = entry;

    DEBUGMSGT(("ftsPtpTable:entry:create", "row 0x%x\n", (uintptr_t)row));
    entry->ftsPtpSlot = ftsPtpSlot;
    entry->ftsPtpError = ftsPtpError;
    entry->ftsPtpMode = ftsPtpMode;
    entry->ftsPtpSynRate = ftsPtpSynRate;
    entry->ftsPtpDelayRate = ftsPtpDelayRate;
    netsnmp_tdata_row_add_index( row, ASN_INTEGER,
                                 &(entry->ftsPtpSlot),
                                 sizeof(entry->ftsPtpSlot));
    if (table_data)
        netsnmp_tdata_add_row( table_data, row);
    return row;
}

void ptp_board_init(netsnmp_tdata *table_data)
{
	int i;
	struct can_frame can_send;
	struct can_frame can_recv;
	int ret;
	int err;
	int canid;

///test
	ftsPtpTable_createEntry(table_data, 2, 1, 0, 0, 0);
	return;


	ptp_board.num = 0;
	
	for (i = 0; i<3; i++)
	{
		ptp_board.slot[i] = 0;
	}
	
	for (i = 0; i<3; i++)
	{
		canid = fts_can_mk_send_id(i, FTS_BOARD_TYPE_PTP);
		fts_can_make_scalar_frame_ptp_poll(&can_send, canid);
		ret = fts_can_send_and_recv(&can_send, &can_recv);
		if (ret != 0)
			continue;
		fts_can_parse_scalar_frame_ptp_poll_reply(&can_recv,&err);
		
		ftsPtpTable_createEntry(table_data, i, err, 0, 0, 0);
		
		ptp_board.slot[ptp_board.num] = 1;
		ptp_board.num++;	
	}
}


void
init_ftsPtpTable(void)
{
	/* here we initialize all the tables we're planning on supporting */
	initialize_table_ftsPtpTable();
}


/** Initialize the ftsRefTable table by defining its contents and how it's structured */
void
initialize_table_ftsPtpTable(void)
{
    const oid ftsPtpTable_oid[] = {1,3,6,1,4,1,63000,2,1,13,1,2,1,11,2};
    const size_t ftsPtpTable_oid_len   = OID_LENGTH(ftsPtpTable_oid);
    netsnmp_handler_registration    *reg;
    netsnmp_tdata                   *table_data;
    netsnmp_table_registration_info *table_info;
    DEBUGMSGTL(("ftsPtpTable:init", "initializing table ftsPtpTable\n"));

    reg = netsnmp_create_handler_registration(
              "ftsPtpTable",     ftsPtpTable_handler,
              ftsPtpTable_oid, ftsPtpTable_oid_len,
              HANDLER_CAN_RWRITE
              );

    table_data = netsnmp_tdata_create_table( "ftsPtpTable", 0 );
    if (NULL == table_data) {
        snmp_log(LOG_ERR,"error creating tdata table for ftsPtpTable\n");
        return;
    }
	//ftsPtpTable_data_load(table_data);
    table_info = SNMP_MALLOC_TYPEDEF( netsnmp_table_registration_info );
    if (NULL == table_info) {
        snmp_log(LOG_ERR,"error creating table info for ftsPtpTable\n");
        return;
    }
    netsnmp_table_helper_add_indexes(table_info,
                           ASN_INTEGER,  /* index: ftsPtpIndex */
                           0);

    table_info->min_column = COLUMN_FTSPTPSLOT;
    table_info->max_column = COLUMN_FTSPTPDELAYRATE;
    
    netsnmp_tdata_register( reg, table_data, table_info );
	ptp_board_init(table_data);

    /* Initialise the contents of the table here */
}



/* remove a row from the table */
void
ftsPtpTable_removeEntry(netsnmp_tdata     *table_data, 
                 netsnmp_tdata_row *row) {
    struct ftsPtpTable_entry *entry;

    if (!row)
        return;    /* Nothing to remove */

    DEBUGMSGT(("ftsPtpTable:entry:remove", "row 0x%x\n", (uintptr_t)row));

    entry = (struct ftsPtpTable_entry *)row->data;
    SNMP_FREE( entry );   /* XXX - release any other internal resources */

    if (table_data)
        netsnmp_tdata_remove_and_delete_row( table_data, row );
    else
        netsnmp_tdata_delete_row( row );    
}


/** handles requests for the ftsPtpTable table */
int
ftsPtpTable_handler(
    netsnmp_mib_handler               *handler,
    netsnmp_handler_registration      *reginfo,
    netsnmp_agent_request_info        *reqinfo,
    netsnmp_request_info              *requests) {

    netsnmp_request_info       *request;
    netsnmp_table_request_info *table_info;
    netsnmp_tdata              *table_data;
    netsnmp_tdata_row          *table_row;
    struct ftsPtpTable_entry          *table_entry;
    int                         ret;

	table_data = netsnmp_tdata_extract_table(requests);

    DEBUGMSGTL(("ftsPtpTable:handler", "Processing request (%d)\n", reqinfo->mode));

    switch (reqinfo->mode) {
     /*
         * Read-support (also covers GetNext requests)
         */
    case MODE_GET:
        for (request=requests; request; request=request->next) {
            if (request->processed)
                continue;

            table_entry = (struct ftsPtpTable_entry *)
                              netsnmp_tdata_extract_entry(request);
            table_info  =     netsnmp_extract_table_info( request);



			////////////////////////////
			unsigned int canid;
			struct can_frame can_send;
			struct can_frame can_recv;
			int flag;
			long mode;
			long synRate;
			long delayRate;

			canid = fts_can_mk_send_id(table_entry->ftsPtpSlot, FTS_BOARD_TYPE_PTP);
			fts_can_make_scalar_frame_ptp_poll(&can_send, canid);
			ret = fts_can_send_and_recv(&can_send, &can_recv);

#if 1 //test
			if (ret != 0)
			{
				netsnmp_tdata_remove_and_delete_row(table_data,netsnmp_tdata_extract_row(request));
			}
#endif
			fts_can_parse_scalar_frame_ptp_poll_reply(&can_recv,&flag);
			table_entry->ftsPtpError = flag;

			fts_can_make_scalar_frame_ptp_get_state(&can_send, canid);
			ret = fts_can_send_and_recv(&can_send, &can_recv);

#if 0	//test
			if (ret != 0)
			{
				netsnmp_tdata_remove_and_delete_row(table_data,netsnmp_tdata_extract_row(request));
			}

			fts_can_parse_scalar_frame_ptp_get_state_reply(&can_recv,&mode, &synRate, &delayRate);
			table_entry->ftsPtpMode= mode;
			table_entry->ftsPtpSynRate= synRate;
			table_entry->ftsPtpDelayRate= delayRate;
#endif
    
            switch (table_info->colnum) {
            case COLUMN_FTSPTPSLOT:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer(request->requestvb, ASN_INTEGER,
                                            table_entry->ftsPtpSlot);
                break;
            case COLUMN_FTSPTPERROR:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER,
                                            table_entry->ftsPtpError);
                break;
            case COLUMN_FTSPTPMODE:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER,
                                            table_entry->ftsPtpMode);
                break;
            case COLUMN_FTSPTPSYNRATE:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER,
                                            table_entry->ftsPtpSynRate);
                break;
            case COLUMN_FTSPTPDELAYRATE:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER,
                                            table_entry->ftsPtpDelayRate);
                break;
            default:
                netsnmp_set_request_error(reqinfo, request,
                                          SNMP_NOSUCHOBJECT);
                break;
            }
        }
        break;

        /*
         * Write-support
         */
    case MODE_SET_RESERVE1:
        for (request=requests; request; request=request->next) {
            if (request->processed)
                continue;

            table_entry = (struct ftsPtpTable_entry *)
                              netsnmp_tdata_extract_entry(request);
            table_info  =     netsnmp_extract_table_info( request);
    
            switch (table_info->colnum) {
            case COLUMN_FTSPTPMODE:
                /* or possibly 'netsnmp_check_vb_int_range' */
                ret = netsnmp_check_vb_int( request->requestvb );
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                break;
			case COLUMN_FTSPTPSYNRATE:
				/* or possibly 'netsnmp_check_vb_int_range' */
				ret = netsnmp_check_vb_int( request->requestvb );
				if ( ret != SNMP_ERR_NOERROR ) {
					netsnmp_set_request_error( reqinfo, request, ret );
					return SNMP_ERR_NOERROR;
				}
				break;
			case COLUMN_FTSPTPDELAYRATE:
				/* or possibly 'netsnmp_check_vb_int_range' */
				ret = netsnmp_check_vb_int( request->requestvb );
				if ( ret != SNMP_ERR_NOERROR ) {
					netsnmp_set_request_error( reqinfo, request, ret );
					return SNMP_ERR_NOERROR;
				}
				break;
            default:
                netsnmp_set_request_error( reqinfo, request,
                                           SNMP_ERR_NOTWRITABLE );
                return SNMP_ERR_NOERROR;
            }
        }
        break;

    case MODE_SET_RESERVE2:
		/*
        for (request = requests; request; request = request->next) {
            table_row = netsnmp_tdata_extract_row(request);
            table_info = netsnmp_extract_table_info(request);


            switch (table_info->colnum) {
            case COLUMN_FTSPTPDOMAIN:
            case COLUMN_FTSPTPDELAYRESPS:
                if (!table_row) {
                    table_row =
                        ftsPtpTable_createEntry(table_data,
                                               *table_info->indexes->val.
                                               integer);
                    if (table_row) {
                        netsnmp_insert_tdata_row(request, table_row);
                    } else {
                        netsnmp_set_request_error(reqinfo, request,
                                                  SNMP_ERR_RESOURCEUNAVAILABLE);
                        return SNMP_ERR_NOERROR;
                    }
                }
                break;
            }
        }

        */


        break;

    case MODE_SET_FREE:
        break;

    case MODE_SET_ACTION:
        for (request=requests; request; request=request->next) {
			
			int canid;
			struct can_frame can_send;
			struct can_frame can_recv;
			int mode,synRate,delayRate;

            if (request->processed)
                continue;

            table_entry = (struct ftsPtpTable_entry *)
                              netsnmp_tdata_extract_entry(request);
            if (table_entry == NULL)
            	continue;
            table_info  =  netsnmp_extract_table_info( request);

			
    
			canid = fts_can_mk_send_id(table_entry->ftsPtpSlot, FTS_BOARD_TYPE_PTP);
            switch (table_info->colnum) {
            case COLUMN_FTSPTPMODE:
				mode = *request->requestvb->val.integer;
                table_entry->ftsPtpMode = *request->requestvb->val.integer;
				fts_can_make_scalar_frame_ptp_set_mode(&can_send, canid, mode);
				ret = fts_can_send_and_recv(&can_send, &can_recv);
				
				if (ret != -1)
				{
					table_entry->ftsPtpMode = mode;
				}
                break;
			case COLUMN_FTSPTPSYNRATE:
				synRate = *request->requestvb->val.integer;
				table_entry->ftsPtpSynRate = *request->requestvb->val.integer;
				fts_can_make_scalar_frame_ptp_set_param(&can_send,canid, table_entry->ftsPtpSynRate, synRate);
				ret = fts_can_send_and_recv(&can_send, &can_recv);
				if (ret != -1)
				{
					table_entry->ftsPtpSynRate = synRate;
				}
				
				break;
			case COLUMN_FTSPTPDELAYRATE:
				delayRate = *request->requestvb->val.integer;
				fts_can_make_scalar_frame_ptp_set_param(&can_send, canid, table_entry->ftsPtpSynRate, delayRate);
				ret = fts_can_send_and_recv(&can_send, &can_recv);
				if (ret != -1)
				{
					table_entry->ftsPtpSynRate = delayRate;
				}
				break;
            }
			
        }
        break;
    case MODE_SET_UNDO:
	/*
        for (request=requests; request; request=request->next) {
            if (request->processed)
                continue;

            table_entry = (struct ftsPtpTable_entry *)
                              netsnmp_tdata_extract_entry(request);
            table_row   =     netsnmp_tdata_extract_row(request);
            table_data  =     netsnmp_tdata_extract_table(request);
            table_info  =     netsnmp_extract_table_info( request);
    
            switch (table_info->colnum) {
            case COLUMN_FTSPTPDOMAIN:
                table_entry->ftsPtpDomain     = table_entry->old_ftsPtpDomain;
                table_entry->old_ftsPtpDomain = 0;
                break;
            }
        }
	*/
        break;
    case MODE_SET_COMMIT:
        break;
    }
    return SNMP_ERR_NOERROR;
}
