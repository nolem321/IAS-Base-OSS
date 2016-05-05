PROGRAM com::examples::basic::loop01(
            VAR p1 AS Integer : "IAS/DM/Default",
            VAR input AS Customer : "http://www.examples.org/akc",
            VAR output AS Customer : "http://www.examples.org/akc")  BEGIN

    VAR i AS Integer : "IAS/DM/Default";

    i=0;

    WHILE (i < 10) DO
      BEGIN

        VAR a AS Address : "http://www.examples.org/akc";

        IF ((i MOD 2) == 0) THEN
          BEGIN
            a=NEW Address : "http://www.examples.org/akc";
          END
        ELSE
          a=NEW Address : "http://www.examples.org/akcf";
        a.street="Nowa";
        a.block=i;
        input.address=a;
        i=(i + 1);
      END;

    i=0;

    WHILE (i < SIZEOF(input.address)) DO
      BEGIN

        VAR tmp AS Address : "http://www.examples.org/akc";

        tmp=input.address[i];

        IF  NOT  ISNULL (tmp) THEN
          BEGIN
            IF tmp ISINSTANCE (Address: "http://www.examples.org/akc") THEN
              BEGIN
                tmp.street=((TYPE(tmp) + ":") + TYPENS(tmp));
              END;
            tmp.block=(STRLEN(tmp.street) + i);
          END;

        i=(i + 1);
      END;

    output=COPYOF(input);
  END;
