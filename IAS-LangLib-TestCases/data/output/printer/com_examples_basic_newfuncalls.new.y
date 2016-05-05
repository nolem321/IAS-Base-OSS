PROGRAM com::examples::basic::newfuncalls(
            VAR p1 AS Integer : "IAS/DM/Default",
            VAR input AS Customer : "http://www.examples.org/akc",
            VAR output AS Customer : "http://www.examples.org/akc")  BEGIN

    VAR a AS Integer : "IAS/DM/Default";
    VAR b AS Integer : "IAS/DM/Default";
    VAR c AS Integer : "IAS/DM/Default";

    c=NULL;

    com::examples::basic::testnull(a,b,c);
  END;
