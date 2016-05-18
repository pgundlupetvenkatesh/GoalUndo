/**
 * Unit Tests for GoalUndo class
**/

#include <gtest/gtest.h>
#include "GoalUndo.h"
 
class GoalUndoTest : public ::testing::Test
{
	protected:
		GoalUndoTest(){}
		virtual ~GoalUndoTest(){}
		virtual void SetUp(){}
		virtual void TearDown(){}
};

TEST(GoalUndoTest, getGoalEmpty)	//Checking for Empty Goal
{
	GoalUndo gTest;
	ASSERT_EQ("", gTest.getGoal());
}

TEST(GoalUndoTest, getOperationsEmpty)	//Checking for empty operations
{
	GoalUndo gTest;
	ASSERT_EQ("", gTest.getOperations());
}

TEST(GoalUndoTest, getOperationsValidGoalInvalidOperation)	//A Goal without operation. Trying to get the operation name.
{
	GoalUndo gTest;
	gTest.addOperation("BuildBike", "");
	ASSERT_EQ("", gTest.getOperations());
}

TEST(GoalUndoTest, getGoalValidGoalInvalidOperation)	//A Goal without operation. Trying to get the Goal name.
{
	GoalUndo gTest;
	gTest.addOperation("BuildBike", "");
	ASSERT_EQ("", gTest.getGoal());
}

TEST(GoalUndoTest, getOperationsInvalidGoalValidOperation)	//An operation without a goal and trying to get the operation name.
{
	GoalUndo gTest;
	gTest.addOperation("", "FixTyre");
	ASSERT_EQ("", gTest.getOperations());
}

TEST(GoalUndoTest, getOperationsInvalidGoalInvalidOperation)	//Neither Goal or Operation. Trying for not-equal assertion.
{
	GoalUndo gTest;
	gTest.addOperation("", "");
	ASSERT_NE("FixTyre", gTest.getOperations());
}

TEST(GoalUndoTest, getOperationsFirstGoalFirstOperation)	//Verifying operation name.
{
	GoalUndo gTest;
	gTest.addOperation("BuildCar", "FixHeadLamps");
	ASSERT_EQ("FixHeadLamps", gTest.getOperations());
}

TEST(GoalUndoTest, getOperationsDuplicateGoalUniqueOperation)	//Having multiple Goals with unique operation names and asserting operation
{
	GoalUndo gTest;
	gTest.addOperation("BuildMotorBike", "FixTyre");
	gTest.addOperation("BuildHouse", "BuildFoundation");
	ASSERT_EQ("BuildFoundation", gTest.getOperations());
}

TEST(GoalUndoTest, getOperationsOneGoal2Operation)	//Two operations having same goal, and getting all operation names.
{
	GoalUndo gTest;
	gTest.addOperation("BuildHome", "BuildFoundation");
	gTest.addOperation("buildSupportingBeams");
	ASSERT_EQ("BuildFoundation buildSupportingBeams", gTest.getOperations());
}

TEST(GoalUndoTest, invalidAddOperation)		//Adding invalid operation and asserting the same
{
	GoalUndo gTest;
	gTest.addOperation("");
	ASSERT_EQ("", gTest.getOperations());
}

TEST(GoalUndoTest, newAddOperationSameGoal)	//Adding just operation name and verifying the same
{
	GoalUndo gTest;
	gTest.addOperation("IgniteFire");
	ASSERT_EQ("IgniteFire", gTest.getOperations());
}

TEST(GoalUndoTest, validgetGoal)	//Adding Goal and Operation. Verifying goal name.
{
	GoalUndo gTest;
	gTest.addOperation("ReachIndia", "BookFlightTickets");
	ASSERT_EQ("ReachIndia", gTest.getGoal());
}

TEST(GoalUndoTest, emptygetGoalWithOperation)	//An operation without a goal and trying to get the Goal name.
{
	GoalUndo gTest;
	gTest.addOperation("", "HireCab");
	ASSERT_EQ("", gTest.getGoal());
}

TEST(GoalUndoTest, undoOperationWithoutParam)	//undo operation without adding one and asserting for the same.
{
	GoalUndo gTest;
	gTest.undoOperation();
	ASSERT_EQ("", gTest.getOperations());
}

TEST(GoalUndoTest, undoOperationWithoutParamAndGoals)	//Undo operation without parameter
{
	GoalUndo gTest;
	gTest.addOperation("BuildHome", "BuildFoundation");
	gTest.addOperation("BuildSupportingBeam");
	gTest.addOperation("BuildWalls");
	gTest.undoOperation();
	ASSERT_EQ("BuildFoundation BuildSupportingBeam", gTest.getOperations());
}

TEST(GoalUndoTest, undoOperationWithoutParamAndOneGoal)	//Undo operation and assert for the same.
{
	GoalUndo gTest;
	gTest.addOperation("StartANewLife", "ErasePast");
	gTest.undoOperation();
	ASSERT_EQ("", gTest.getOperations());
}

TEST(GoalUndoTest, undoOperationEmptyWithoutGoal)	//Undo operation empty string
{
	GoalUndo gTest;
	gTest.undoOperation("");
	ASSERT_EQ("", gTest.getOperations());
}

TEST(GoalUndoTest, undoOperation)	//Adding operations for the same goal and undoing it. asserting for operation names.
{
	GoalUndo gTest;
	gTest.addOperation("BuildBike", "FixTyre");
	gTest.addOperation("PaintJob");
	gTest.addOperation("BuildEngine");
	gTest.undoOperation("BuildEngine");
	ASSERT_EQ("FixTyre PaintJob", gTest.getOperations());
}

TEST(GoalUndoTest, undoInvalidOperation)	//Adding operations to the same goal and undoing an invalid operation.
{
	GoalUndo gTest;
	gTest.addOperation("BuildCar", "BuildEngine");
	gTest.addOperation("BuildChassis");
	gTest.addOperation("BuildBody");
	gTest.undoOperation("PaintJob");
	ASSERT_EQ("BuildEngine BuildChassis BuildBody", gTest.getOperations());
}

TEST(GoalUndoTest, undoOperationWithMultipleGoals)	//Adding multiple goals and opearions and undoing operations
{
	GoalUndo gTest;
	gTest.addOperation("BuildHome", "BuildWall");
	gTest.addOperation("BuildSupportingBeam");
	gTest.addOperation("BuildFoundation", "SurveyLand");
	gTest.addOperation("MixCement");
	gTest.addOperation("LayFoundationStones");
	gTest.undoOperation("MixCement");
	gTest.undoOperation("BuildSupportingBeam");
	ASSERT_NE("BuildWall BuildSupportingBeam", gTest.getOperations());
}

TEST(GoalUndoTest, undoGoalEmpty)	//undo Goal and assert for operations
{
	GoalUndo gTest;
	gTest.undoGoal();
	ASSERT_EQ("", gTest.getOperations());
}

TEST(GoalUndoTest, addOpundoOpUndoGoal)	//Adding opearions to a goal and undoing opeartions and goal. Asserting for opeartions.
{
	GoalUndo gTest;
	gTest.addOperation("BuildMotorBike", "BuildChassis");
	gTest.addOperation("BuildEngine");
	gTest.addOperation("FixTyre");
	gTest.addOperation("PaintJob");
	gTest.undoOperation("FixTyre");
	gTest.undoOperation();
	gTest.undoGoal();
	ASSERT_EQ("", gTest.getOperations());
}

TEST(GoalUndoTest, CheckingGoalWithNoOperation)
{
	GoalUndo gTest;
	gTest.addOperation("CompleteMasters", "GettingAdmitted");
	gTest.addOperation("PassPrerequisites");
	gTest.undoGoal();
	gTest.addOperation("CompleteUnderGrad", "CompleteSchooling");
	gTest.addOperation("GetGoodGrades");
	gTest.undoOperation("PassPrerequisites");
	gTest.undoOperation();
	gTest.undoOperation();
	ASSERT_EQ("", gTest.getOperations());
}

TEST(GoalUndoTest, undoGoalSingle)	//Adding operation and undoing goal. Asserting for operation.
{
	GoalUndo gTest;
	gTest.addOperation("WriteTestCases");
	gTest.undoGoal();
	ASSERT_EQ("", gTest.getOperations());
}

TEST(GoalUndoTest, getGoalWithUndoGoal)	//Adding miultiple goals and operations. Undoing goals and operations and asserting goal.
{
	GoalUndo gTest;
	gTest.addOperation("BuildRoom", "BuildFoundation");
	gTest.addOperation("operationTwo");
	gTest.addOperation("goalTwo", "BuildFoundation");
	gTest.addOperation("operationThree");
	gTest.addOperation("operationFour");
	gTest.undoOperation("operationThree");
	gTest.undoOperation();
	gTest.undoGoal();
	ASSERT_EQ("BuildRoom", gTest.getGoal());
}

TEST(GoalUndoTest, getGoalEmptyWithUndoGoal)
{
	GoalUndo gTest;
	gTest.addOperation("BuildHome", "BuildFoundation");
	gTest.addOperation("BuildWall");
	gTest.addOperation("FuxWindowsDoors");
	gTest.undoOperation();
	gTest.undoGoal();
	ASSERT_EQ("", gTest.getGoal());
}

TEST(GoalUndoTest, getGoalAfterUndoGoal)	//Adding operations, undoing it and again adding operations. Asserting for Goal.
{
	GoalUndo gTest;
	gTest.addOperation("BuildBike", "BuildChassis");
	gTest.addOperation("BuildEngine");
	gTest.addOperation("FixTyre");
	gTest.undoOperation();
	gTest.undoGoal();
	gTest.addOperation("BuildCar", "BuildChassis");
	ASSERT_EQ("BuildCar", gTest.getGoal());
}

TEST(GoalUndoTest, undoAllOperationsLeavingGoal)
{
	GoalUndo gTest;
	gTest.addOperation("BuildPC", "getComponents");
	gTest.addOperation("InterconnectComponents");
	gTest.undoOperation();
	gTest.undoOperation("getComponents");
	ASSERT_EQ("BuildPC", gTest.getGoal());
}

TEST(GoalUndoTest, errorInGetGoal)	//Test case fails when added operation and undoing the same operation. Asserting for a goal name.
{
	GoalUndo gTest;
	gTest.addOperation("TravelAroundTheWorld", "EarnMoney");
	gTest.undoOperation("EarnMoney");
	ASSERT_EQ("", gTest.getGoal());
}

TEST(GoalUndoTest, undoOperationGoalAssertForGoal)	//Adding an operation undoing it and getting Goal
{
	GoalUndo gTest;
	gTest.addOperation("getComponents");
	gTest.addOperation("BuildPC", "InterconnectComponents");
	gTest.undoOperation();
	//gTest.undoGoal();
	ASSERT_EQ("getComponents", gTest.getGoal());
}

/*TEST(GoalUndoTest, segFaultGetGoal)	//Gives a seg fault
{
	GoalUndo gTest;
	gTest.addOperation("operationOne");
	gTest.undoOperation("operationOne");
	gTest.undoOperation();
	ASSERT_EQ("", gTest.getGoal());
}*/

/*TEST(GoalUndoTest, segFaultGetOperations)
{
	GoalUndo gTest;
	gTest.addOperation("operationOne");
	gTest.undoOperation("operationOne");
	gTest.undoOperation();
	ASSERT_EQ("", gTest.getOperations());
}*/
