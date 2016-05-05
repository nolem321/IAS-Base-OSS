PROGRAM com::examples::basic::loop03(
            VAR p1 AS Integer : "IAS/DM/Default",
            VAR input AS Customer : "http://www.examples.org/akc",
            VAR output AS Customer : "http://www.examples.org/akc")  BEGIN

    VAR i AS Integer : "IAS/DM/Default";

    FOR i = 1 TO 10 DO
      BEGIN

        VAR a AS Address : "http://www.examples.org/akc";

        a=NEW Address : "http://www.examples.org/akcf";
        a.street="Nowa";
        a.block=i;
        input.address=a;
      END;

    FOR input.address[0].block = 0 TO SIZEOF(input.address) STEP 2 DO
      BEGIN

        VAR tmp AS Address : "http://www.examples.org/akc";

        tmp=input.address[input.address[0].block];

        IF  NOT  ISNULL (tmp) THEN
          tmp.street=(((TYPE(tmp) + ":") + TYPENS(tmp)) + " ! ");
      END;

    output=COPYOF(input);
  END;
