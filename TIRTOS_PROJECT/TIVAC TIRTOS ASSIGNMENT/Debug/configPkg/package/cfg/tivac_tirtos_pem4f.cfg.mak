# invoke SourceDir generated makefile for tivac_tirtos.pem4f
tivac_tirtos.pem4f: .libraries,tivac_tirtos.pem4f
.libraries,tivac_tirtos.pem4f: package/cfg/tivac_tirtos_pem4f.xdl
	$(MAKE) -f C:\Users\Jett\DOCUME~1\CPE403~1\IVWORK~1\RTOS\TIRTOS~1\TIVACT~1/src/makefile.libs

clean::
	$(MAKE) -f C:\Users\Jett\DOCUME~1\CPE403~1\IVWORK~1\RTOS\TIRTOS~1\TIVACT~1/src/makefile.libs clean

