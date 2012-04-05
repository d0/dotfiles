
class key_distribution_protocol:
	def __init__(self,
			mode=1,
			keys_in_list=4, 
			key_length=16, 
			seed_length=8,
			timeout=15):
		
		# Parameters
		self.mode 		= mode
		self.mode_length	= 1					# 1 byte to save key distro mode
		self.keys_in_list 	= keys_in_list
		self.timeout 		= timeout 				# in sec
		self.wep_key_length 	= key_length				# 64/128/152/256 bit oder 8,16,19,32 byte
		self.t_stamp_length	= 8					# byte (ntp standard)
		self.seed_length	= seed_length				# byte; md5 accepts everything
		self.macID_length	= 6					# byte; ethernet-mac
		
		# locals
		session_time		= self.keys_in_list * self.timeout

	def req(self):
		return self.macID_length + self.mode_length
	
	def rep(self):
		if self.mode == 1:
			return self.keys_in_list * self.wep_key_length + self.t_stamp_length	
		elif self.mode == 2:
			return self.seed_length + self.t_stamp_length	


class tls:
	def __init__(self,
			block_size=8, 			# Byte
			MAC_size=16, 
			self_signed_cert_size=750, 
			cert_size=1500):
			
		self.block_size		= block_size
		self.MAC_size		= MAC_size
		self.self_signed_cert_size = self_signed_cert_size
		self.cert_size 		= cert_size
		
	def session_setup(self):
		# Note: tls values should be should be understood as indications and
		# include ethernet and tcp/ip frameheader
		
		# tls-session setup overhead 
		overhead = 500	# client: handshake proto: hello
		overhead += 500 + self.self_signed_cert_size	# server: handshake proto: hello; self-signed cert; mutual auth for MobiSEC
		overhead += 250 	# server: kex, hello done
		overhead += 250 	# client: kex; change cipher spec; enc handshake
		overhead += self.cert_size	# client: signed cert; mutual auth for MobiSEC
		overhead += 350	# server: enc handshake msg; change cipher spec; enc handshake msg	
		
		return overhead
		
		
	def resume_session(self):
		# Note: tls values should be should be understood as indications and
		# include ethernet and tcp/ip frameheader
		
		# tls-session resume overhead (iff session ID accepted by server)
		overhead = 500	# client: handshake proto: hello (using the session ID)
		overhead += 500	# server: handshake proto: hello (iff session ID accepted)
		overhead += 50	# client: change cipher spec; finished msg
		overhead += 50	# server: change cipher spec; finished msg
		
		return overhead
		
	# for now only to take note	
	def handshake(self, payload):
		data = payload
		data += 4		# TLS handshake header
		return data	
	
	def record(self, payload):
		
		padding = payload % self.block_size
		data = payload + padding
	
		data += self.MAC_size	# MD5-hash: 0, 16 or 20 Byte; adding MAC (integrity check)
		data += 5 		# TLS record proto header
	
		return data
		
		
		
def main():
	print "Protocol class to compute protocol specific overhead"
	
	
	
if __name__ == "__main__":
	main()
