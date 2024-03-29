#include "ping.h"

void
network_error_echo (ping_t * ping)
{
	/* throw away */
	if (ping->sender.sequence > 1)
		--ping->sender.sequence;
	--ping->receiver.sequence;
	if (ping->flag.verbose)
	{
		printf ("%d bytes from %s: Loop-back Type=%d Code=%d\n",
				ping->receiver.bytes - IP_HEADER_SIZE,
				ping->destination,
				ping->receiver.header.icmp->type,
				ping->receiver.header.icmp->code);
	}
}

void
network_error_time_exceeded (ping_t * ping)
{
	++ping->error;
	switch (ping->receiver.header.icmp->code)
	{
		case 0:
			printf ("%d bytes from %s: icmp_seq=%d Time to live exceeded\n",
				ping->receiver.bytes - IP_HEADER_SIZE,
				ping->destination,
				ping->receiver.sequence);
			break;

		case 1:
			printf ("%d bytes from %s: icmp_seq=%d Fragment reassembly time exceeded\n",
				ping->receiver.bytes - IP_HEADER_SIZE,
				ping->destination,
				ping->receiver.sequence);
			break;
	}
}

void
network_error_default (ping_t * ping)
{
	++ping->error;
	printf ("%d bytes from %s: icmp_seq=%d Unexpected type %d.%d\n",
			ping->receiver.bytes - IP_HEADER_SIZE,
			ping->destination,
			ping->receiver.sequence,
			ping->receiver.header.icmp->type,
			ping->receiver.header.icmp->code);
}
