PROGRAM com::examples::basic::loop02(
            VAR p1 AS Integer : "IAS/DM/Default",
            VAR input AS Customer : "http://www.examples.org/akc",
            VAR output AS Customer : "http://www.examples.org/akc")  BEGIN

    VAR i AS Integer : "IAS/DM/Default";
    VAR i2 AS Integer : "IAS/DM/Default";

    output=COPYOF(input);

    FOR i = 1 TO 100 DO
      BEGIN

        VAR a AS Address : "http://www.examples.org/akc";

        a=NEW Address : "http://www.examples.org/akcf";
        a.street="Nowa";
        a.block=i;
        output.address=a;
      END;
  END;
