/* A complete module file will, typically,
 * have two, possibly, three sections (called fragments)
 * A global module fragment – this is where we include things we need (optional)
 * The main module purview – Where we can export types and behaviour
 * A private fragment – this ends the portion of the module interface that can affect the behaviour of other translation
 * units (optional)
 * The global fragment must precede the main purview
 * and is simply introduced using the keyword: module */
module;  // Start of global fragment
export module moduleA;

// export void func() {}