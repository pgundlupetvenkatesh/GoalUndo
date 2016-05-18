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

TEST(GoalUndoTest, getGoalEmpty)
{
	GoalUndo gTest;
	ASSERT_EQ("", gTest.getGoal());
}

TEST(GoalUndoTest, getOperationsEmpty)
{
	GoalUndo gTest;
	ASSERT_EQ("", gTest.getOperations());
}

TEST(GoalUndoTest, getOperationsValisGoalInvalidOperation)
{
	GoalUndo gTest;
	gTest.addOperation("BuildBike", "");
	ASSERT_EQ("", gTest.getOperations());
}

TEST(GoalUndoTest, getOperationsInvalisGoalValidOperation)
{
	GoalUndo gTest;
	gTest.addOperation("", "FixTyre");
	ASSERT_EQ("", gTest.getOperations());
}

TEST(GoalUndoTest, getOperationsInvalisGoalInvalidOperation)
{
	GoalUndo gTest;
	gTest.addOperation("", "");
	ASSERT_NE("FixTyre", gTest.getOperations());
}

TEST(GoalUndoTest, getOperationsFirstGoalFirstOperation)
{
	GoalUndo gTest;
	gTest.addOperation("BuildCar", "FixHeadLamps");
	ASSERT_EQ("FixHeadLamps", gTest.getOperations());
}

TEST(GoalUndoTest, getOperationsDuplicateGoalUniqueOperation)
{
	GoalUndo gTest;
	gTest.addOperation("BuildMotorBike", "FixTyre");
	gTest.addOperation("BuildHouse", "BuildFoundation");
	ASSERT_EQ("BuildFoundation", gTest.getOperations());
}

TEST(GoalUndoTest, getOperationsOneGoal2Operation)
{
	GoalUndo gTest;
	gTest.addOperation("BuildHome", "BuildFoundation");
	gTest.addOperation("buildSupportingBeams");
	ASSERT_EQ("BuildFoundation buildSupportingBeams", gTest.getOperations());
}

TEST(GoalUndoTest, invalidAddOperation)
{
	GoalUndo gTest;
	gTest.addOperation("");
	ASSERT_EQ("", gTest.getOperations());
}

TEST(GoalUndoTest, newAddOperationSameGoal)
{
	GoalUndo gTest;
	gTest.addOperation("IgniteFire");
	ASSERT_EQ("IgniteFire", gTest.getOperations());
}

TEST(GoalUndoTest, validgetGoal)
{
	GoalUndo gTest;
	gTest.addOperation("ReachIndia", "BookFlightTickets");
	ASSERT_EQ("ReachIndia", gTest.getGoal());
}

TEST(GoalUndoTest, emptygetGoalWithOperation)
{
	GoalUndo gTest;
	gTest.addOperation("", "HireCab");
	ASSERT_EQ("", gTest.getGoal());
}

TEST(GoalUndoTest, undoOperationWithoutParam)
{
	GoalUndo gTest;
	gTest.undoOperation();
	ASSERT_EQ("", gTest.getOperations());
}

TEST(GoalUndoTest, undoOperationWithoutParamAndGoals)
{
	GoalUndo gTest;
	gTest.addOperation("BuildHome", "BuildFoundation");
	gTest.addOperation("BuildSupportingBeam");
	gTest.addOperation("BuildWalls");
	gTest.undoOperation();
	ASSERT_EQ("BuildFoundation BuildSupportingBeam", gTest.getOperations());
}

TEST(GoalUndoTest, undoOperationWithoutParamAndOneGoal)
{
	GoalUndo gTest;
	gTest.addOperation("StartANewLife", "ErasePast");
	gTest.undoOperation();
	ASSERT_EQ("", gTest.getOperations());
}

TEST(GoalUndoTest, undoOperationEmptyWithoutGoal)
{
	GoalUndo gTest;
	gTest.undoOperation("");
	ASSERT_EQ("", gTest.getOperations());
}

TEST(GoalUndoTest, undoOperation)
{
	GoalUndo gTest;
	gTest.addOperation("BuildBike", "FixTyre");
	gTest.addOperation("PaintJob");
	gTest.addOperation("BuildEngine");
	gTest.undoOperation("BuildEngine");
	ASSERT_EQ("FixTyre PaintJob", gTest.getOperations());
}

TEST(GoalUndoTest, undoInvalidOperation)
{
	GoalUndo gTest;
	gTest.addOperation("BuildCar", "BuildEngine");
	gTest.addOperation("BuildChassis");
	gTest.addOperation("BuildBody");
	gTest.undoOperation("PaintJob");
	ASSERT_EQ("BuildEngine BuildChassis BuildBody", gTest.getOperations());
}

TEST(GoalUndoTest, undoOperationWithMultipleGoals)
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

TEST(GoalUndoTest, undoGoalEmpty)
{
	GoalUndo gTest;
	gTest.undoGoal();
	ASSERT_EQ("", gTest.getOperations());
}

TEST(GoalUndoTest, addOpundoOpUndoGoal)
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

TEST(GoalUndoTest, undoGoalSingle)
{
	GoalUndo gTest;
	gTest.addOperation("WriteTestCases");
	gTest.undoGoal();
	ASSERT_EQ("", gTest.getOperations());
}

TEST(GoalUndoTest, getGoalWithUndoGoal)
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

TEST(GoalUndoTest, getGoalAfterUndoGoal)
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

TEST(GoalUndoTest, undoOAllperationsLeavingGoal)
{
	GoalUndo gTest;
	gTest.addOperation("BuildPC", "getComponents");
	gTest.addOperation("InterconnectComponents");
	gTest.undoOperation();
	gTest.undoOperation("getComponents");
	ASSERT_EQ("BuildPC", gTest.getGoal());
}

TEST(GoalUndoTest, errorInGetGoal)
{
	GoalUndo gTest;
	gTest.addOperation("TravelAroundTheWorld", "EarnMoney");
	gTest.undoOperation("EarnMoney");
	ASSERT_EQ("", gTest.getGoal());
}

/*TEST(GoalUndoTest, segFaultGetGoal)
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
