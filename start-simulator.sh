#! /bin/sh

sleep 1
echo "********* SoccerServer **********"
BIN="SoccerServer"
DES="/home/mix-real/Server/mr-soccer_istanbul"
#cd soccer/soccer_server/
cd $DES/soccer/soccer_server
#cd /home/pooya/mix-real/mr-soccer
xterm -e "./$BIN" &

sleep 0
echo "********* Graphic Module **********"
BIN="KoblenzGraphics"
#cd graphics/trunk/
cd $DES/graphics/trunk
xterm -e "./$BIN" &


sleep 2
echo "********* MR-Simulator **********"
BIN="MR_Simulator"
cd $DES/mr-simulator/soccer_simulator
xterm -e "./$BIN " &

sleep 0
echo "********* OperatorServer **********"
BIN="VisualOperator"
cd $DES/soccer/soccer_visual_operator
xterm -e "./$BIN" &


#sleep 0
#echo "********* SoccerClient ***********"
#cd /home/pooya/mix-real/istanbul/TripleA-2.4
#./start0.sh

#sleep 2
#echo "******** operator ***********"
#BIN="OperatorServer"
#cd $DES/soccer/soccer_operator
#xterm -e "./$BIN" &

#sleep 2
echo "***********finish************"


