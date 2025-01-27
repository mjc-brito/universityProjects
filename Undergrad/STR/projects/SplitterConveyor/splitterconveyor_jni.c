#include <jni.h>
#include <SplitterConveyor.h>

/*
 * Class:     SplitterConveyor
 * Method:    initializeHardwarePorts
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_SplitterConveyor_initializeHardwarePorts(JNIEnv* ignoreEnv, jclass ignorejClass)
{
	initializeHardwarePorts();
}

/*
 * Class:     SplitterConveyor
 * Method:    cylinderStart_getPosition
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_SplitterConveyor_cylinderStart_1getPosition(JNIEnv* ignoreEnv, jclass ignorejClass)
{
	return cylinderStart_getPosition();
}

/*
 * Class:     SplitterConveyor
 * Method:    cylinderStart_moveForward
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_SplitterConveyor_cylinderStart_1moveForward(JNIEnv* ignoreEnv, jclass ignorejClass)
{
	cylinderStart_moveForward();
}

/*
 * Class:     SplitterConveyor
 * Method:    cylinderStart_moveBackward
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_SplitterConveyor_cylinderStart_1moveBackward(JNIEnv* ignoreEnv, jclass ignorejClass)
{
	cylinderStart_moveBackward();
}

/*
 * Class:     SplitterConveyor
 * Method:    cylinderStart_stop
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_SplitterConveyor_cylinderStart_1stop(JNIEnv* ignoreEnv, jclass ignorejClass)
{
	cylinderStart_stop();
}

/*
 * Class:     SplitterConveyor
 * Method:    cylinder1_getPosition
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_SplitterConveyor_cylinder1_1getPosition(JNIEnv* ignoreEnv, jclass ignorejClass)
{
	return cylinder1_getPosition();
}

/*
 * Class:     SplitterConveyor
 * Method:    cylinder1_moveForward
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_SplitterConveyor_cylinder1_1moveForward(JNIEnv* ignoreEnv, jclass ignorejClass)
{
	cylinder1_moveForward();
}

/*
 * Class:     SplitterConveyor
 * Method:    cylinder1_moveBackward
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_SplitterConveyor_cylinder1_1moveBackward(JNIEnv* ignoreEnv, jclass ignorejClass)
{
	cylinder1_moveBackward();
}

/*
 * Class:     SplitterConveyor
 * Method:    cylinder1_stop
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_SplitterConveyor_cylinder1_1stop(JNIEnv* ignoreEnv, jclass ignorejClass)
{
	cylinder1_stop();
}

/*
 * Class:     SplitterConveyor
 * Method:    cylinder2_getPosition
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_SplitterConveyor_cylinder2_1getPosition(JNIEnv* ignoreEnv, jclass ignorejClass)
{
	return cylinder2_getPosition();
}

/*
 * Class:     SplitterConveyor
 * Method:    cylinder2_moveForward
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_SplitterConveyor_cylinder2_1moveForward(JNIEnv* ignoreEnv, jclass ignorejClass)
{
	cylinder2_moveForward();
}

/*
 * Class:     SplitterConveyor
 * Method:    cylinder2_moveBackward
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_SplitterConveyor_cylinder2_1moveBackward(JNIEnv* ignoreEnv, jclass ignorejClass)
{
	cylinder2_moveBackward();
}

/*
 * Class:     SplitterConveyor
 * Method:    cylinder2_stop
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_SplitterConveyor_cylinder2_1stop(JNIEnv* ignoreEnv, jclass ignorejClass)
{
	cylinder2_stop();
}

/*
 * Class:     SplitterConveyor
 * Method:    conveyorMove
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_SplitterConveyor_conveyorMove(JNIEnv* ignoreEnv, jclass ignorejClass)
{
	conveyorMove();
}

/*
 * Class:     SplitterConveyor
 * Method:    conveyorStop
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_SplitterConveyor_conveyorStop(JNIEnv* ignoreEnv, jclass ignorejClass)
{
	conveyorStop();
}

/*
 * Class:     SplitterConveyor
 * Method:    isBrickAtDock1
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_SplitterConveyor_switchDock1Pressed(JNIEnv* ignoreEnv, jclass ignorejClass)
{
	return switchDock1Pressed();
}

/*
 * Class:     SplitterConveyor
 * Method:    isBrickAtDock2
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_SplitterConveyor_switchDock2Pressed(JNIEnv* ignoreEnv, jclass ignorejClass)
{
	return switchDock2Pressed();
}

/*
 * Class:     SplitterConveyor
 * Method:    isBrickAtDockEnd
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_SplitterConveyor_switchDockEndPressed(JNIEnv* ignoreEnv, jclass ignorejClass)
{
	return switchDockEndPressed();
}

/*
 * Class:     SplitterConveyor
 * Method:    getIdentificationSensors
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_SplitterConveyor_getIdentificationSensors(JNIEnv* ignoreEnv, jclass ignorejClass)
{
	return getIdentificationSensors();
}

/*
 * Class:     SplitterConveyor
 * Method:    isBrickAtCylinder1
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_SplitterConveyor_isBrickAtCylinder1(JNIEnv* ignoreEnv, jclass ignorejClass)
{
	return isBrickAtCylinder1();
}

/*
 * Class:     SplitterConveyor
 * Method:    isBrickAtCylinder2
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_SplitterConveyor_isBrickAtCylinder2(JNIEnv* ignoreEnv, jclass ignorejClass)
{
	return isBrickAtCylinder2();
}

/*
 * Class:     SplitterConveyor
 * Method:    turnLEDon
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_SplitterConveyor_turnLEDon(JNIEnv* ignoreEnv, jclass ignorejClass)
{
	turnLEDon();
}

/*
 * Class:     SplitterConveyor
 * Method:    turnLEDoff
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_SplitterConveyor_turnLEDoff(JNIEnv* ignoreEnv, jclass ignorejClass)
{
	turnLEDoff();
}