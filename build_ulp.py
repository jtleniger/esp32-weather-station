import os

print("Compiling ulp_c/ulp.c...")

c_path = os.path.join("ulp_c", "ulp.c")

os.system("ulpcc {}".format(c_path))

s_path = os.path.join("ulp", "ulp.s")

os.replace("ulp.s", s_path)