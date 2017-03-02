# invoke SourceDir generated makefile for Robot.pem4f
Robot.pem4f: .libraries,Robot.pem4f
.libraries,Robot.pem4f: package/cfg/Robot_pem4f.xdl
	$(MAKE) -f C:\Users\Morty\workspace_v6_2\CSRobot_01/src/makefile.libs

clean::
	$(MAKE) -f C:\Users\Morty\workspace_v6_2\CSRobot_01/src/makefile.libs clean

