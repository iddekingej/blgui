cd ../bduild
make test 
if [ $? -eq "2" ];
then
	more Testing/Temporary/LastTest.log
fi
