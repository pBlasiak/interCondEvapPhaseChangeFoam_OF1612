{
	Pair<tmp<volScalarField> > vDotT = mixture->vDotT();
		const volScalarField& vDotcT = vDotT[0]();
		const volScalarField& vDotvT = vDotT[1]();
	    const volScalarField vDotcmvT(vDotcT - vDotvT);

	TSat = mixture->TSat();
    alphat = turbulence->nut()/Prt;
    alphat.correctBoundaryConditions();
	alphaEff = mixture->alphaEff() + alphat;
	cp = mixture->cp();

	fvScalarMatrix TEqn
	(
		  fvm::ddt(T)
		+ fvm::div(phi, T)
	    - fvm::Sp(fvc::div(phi),T)
		- fvm::laplacian(alphaEff, T,"laplacian(alphaEff,T)")
	 ==
		  fvm::Sp(vDotcmvT/rhoCp, T) - vDotcmvT/rhoCp*TSat	
	);

    TEqn.relax();
    TEqn.solve();

    Info<< "min/max(T) = " << min(T).value() << ", "
        << max(T).value() <<endl;
}
