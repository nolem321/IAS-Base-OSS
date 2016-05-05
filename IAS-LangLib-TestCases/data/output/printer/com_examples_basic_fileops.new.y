PROGRAM com::examples::basic::fileops(
            VAR p1 AS Integer : "IAS/DM/Default",
            VAR input AS Customer : "http://www.examples.org/akc",
            VAR output AS Customer : "http://www.examples.org/akc")  BEGIN

    VAR a AS Address : "http://www.examples.org/akc";
    VAR c AS Customer : "http://www.examples.org/akc";
    VAR o AS AnyType : "IAS/DM/Default";

    std::save("stdout",1);

    std::save("stdout",input);

    std::save("/tmp/sdo.out",input);

    c=std::load("/tmp/sdo.out");
    output=COPYOF(input);
    output.misc=c;
  END;
