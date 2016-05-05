PROGRAM com::examples::basic::assign01(
            VAR p1 AS Integer : "IAS/DM/Default",
            VAR input AS Customer : "http://www.examples.org/akc",
            VAR output AS Customer : "http://www.examples.org/akc")  BEGIN

    VAR name AS Name : "http://www.examples.org/akc";
    VAR date AS DateTime : "IAS/DM/Default";

    output=input;
    output.age=10;
    output.firstname="test1";
    output.birth="2000-02-03T10:12:49+0300";
    name=("" + output.birth);
    date=name;
    name=(date +  ( "100" AS Integer : "IAS/DM/Default" ) );
    output.age=date;
    output.middlename=name;
  END;
