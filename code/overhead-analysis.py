#!/usr/bin/python
import sys
import getopt

import protos
from latex import *


# globals
key_distr_modes = {'server_driven':1, 'client_driven':2}

	
	

	
def ether_tcpip_frame(payload):
	return payload+70	# vaguely 
			

def main():
	dotex 			= False

	# Parameter
	keys_in_list	= 15
	key_length		= 16
	seed_length		= 8
	timeout			= 60
	
	session_time	= keys_in_list * timeout

	# using ciphersuite TLS_RSA_WITH_RC4_128_MD5
	tls = protos.tls(	8,	# block size
				16,	# MAC size
				750,	# cert
				1500	# ss_cert
				)
				
	# process cmdline options			
	try:
		opts, args = getopt.getopt(sys.argv[1:], 'o:')
	except getopt.GetoptError, err:
		print str(err) # will print something like "option -a not recognized"
		sys.exit(2)
    
	for o, a in opts:
		if o == "-o":
			dotex = True
			output_file = a
				
				
	
	# key-distr-proto overhead
	kdp = protos.key_distribution_protocol(key_distr_modes['server_driven'], keys_in_list, key_length, seed_length, timeout);	
	key_distr_proto_server_dr = 	ether_tcpip_frame(tls.record(kdp.req()))
	key_distr_proto_server_dr +=	ether_tcpip_frame(tls.record(kdp.rep()))
	
	kdp = protos.key_distribution_protocol(key_distr_modes['client_driven'], keys_in_list, key_length, seed_length, timeout);
	key_distr_proto_client_dr = 	ether_tcpip_frame(tls.record(kdp.req()))
	key_distr_proto_client_dr +=	ether_tcpip_frame(tls.record(kdp.rep()))
	
	roundtrips		= 0
	roundtrips		+= 2	# for handshake proto
	roundtrips		+= 1	# for KDP


	# Normal cmd-line output
	print "Start overhead analysis for one hop"
	print "two-side communication"
	print "===================================\n"
	print "Keys in list:\t\t", keys_in_list
	print "Timeout for key usage:\t", timeout, " sec"
	print "Session time:\t\t", session_time, " sec"
	print
	
	print "On normal tls session setup:"
	print "Overall overhead (server driven):\t\t", (tls.session_setup() + key_distr_proto_server_dr) , " Byte"
	print "Overall overhead (client driven):\t\t", (tls.session_setup() + key_distr_proto_client_dr), " Byte"
	print "Average data rate (relative to timeout):\t", (2*tls.session_setup() + key_distr_proto_server_dr + key_distr_proto_client_dr)/timeout, " Byte/s"
	print 	
	
	print "With tls session resume:"
	print "Overall overhead (server driven):\t\t", (tls.resume_session() + key_distr_proto_server_dr) , " Byte"
	print "Overall overhead (client driven):\t\t", (tls.resume_session() + key_distr_proto_client_dr), " Byte"
	print "Average data rate (relative to timeout):\t", (2*tls.resume_session() + key_distr_proto_server_dr + key_distr_proto_client_dr)/timeout, " Byte/s"
	print
	
	print "Estimated round trips: ", roundtrips
	
	# for tex-output
	texdoc = latex()
	
	texdoc.put("\emph{Ausgangsparameter:}\n")
	texdoc.put("\\begin{tabular}{ll}")
	texdoc.put("Keys in list: & "+ str(keys_in_list) + "\\tabularnewline")
	texdoc.put("Timeout for key usage: & " + str(timeout) + " sec\\tabularnewline")
	texdoc.put("Session time: & " + str(session_time) + " sec\\tabularnewline")
	texdoc.put("\end{tabular}\\\\")
	
	texdoc.put("\emph{Netzwerklast bei einem normalen TLS-Session Setup:}\n")
	texdoc.put("\\begin{tabular}{ll}")
	texdoc.put("Server Driven: & "+ str(tls.session_setup() + key_distr_proto_server_dr) + " Byte\\tabularnewline")
	texdoc.put("Client Driven: & " + str(tls.session_setup() + key_distr_proto_client_dr) + " Byte\\tabularnewline")
	texdoc.put("Datenrate:\\footnotemark & " + str((2*tls.session_setup() + key_distr_proto_server_dr + key_distr_proto_client_dr)/timeout) + " Bytes/sec\\tabularnewline")
	texdoc.put("\end{tabular}\\\\")
	texdoc.put("\\footnotetext{Durchschnittliche Datenrate relative zum Timeout.}")
	
	texdoc.put("\emph{Netzwerklast bei einem TLS-Session Resume:}\n")
	texdoc.put("\\begin{tabular}{ll}")
	texdoc.put("Server Driven: & " + str(tls.resume_session() + key_distr_proto_server_dr) + " Byte\\tabularnewline")
	texdoc.put("Client Driven: & " + str(tls.resume_session() + key_distr_proto_client_dr) + " Byte\\tabularnewline")
	texdoc.put("Datenrate: & " + str((2*tls.resume_session() + key_distr_proto_server_dr + key_distr_proto_client_dr)/timeout) + " Bytes/sec\\tabularnewline")
	texdoc.put("\end{tabular}\\\\")
	
	texdoc.put("\emph{Estimated round trips:\t" + str(roundtrips) + "}")
	
	# generate latex output
	if dotex == True:
		print "---------------------------------"
		print "Writing Results in ", output_file
		texdoc.out(output_file)
	
	
if __name__ == "__main__":
	main()
