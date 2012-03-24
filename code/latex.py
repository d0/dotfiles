


class latex:
	
	def __init__(self):
		self.content = ""

	def put(self,string):
		self.content += str(string) + "\n"
	
	
	def out(self, output_file):
		f = open(output_file, "w")
		f.write(self.content)
		f.close()
