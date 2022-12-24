# Contrat-o-matic:
## Making legal documents easier, one click at a time
#### Video Demo:  <https://youtu.be/pUQnpKSGNhk>
#### Description:
##### Introduction
Law documents tend to be complicated for everyone outside of the legal world. Sometimes people do not make formally-supported legal agreements because they do not understand the documents, or they just cannot afford a lawyer for simple documents that they could make with some little external help.

Contrat-o-matic is a solution that brings an easily understandable tool in order to create basic legal documents. The idea is not to replace the function of lawyers; it is actually giving them more job since approaching people to Law empowers them and makes them aware of their rights!

Contrat-o-matic is a web application based in Flask that contains the core of a more robust and complete digital web service. It is the first functional step of a future solution that makes legal documents more accesible. It is currently written in Spanish and under the standards of Chilean Law.
##### Files description
As a web application, the project folder has a static folder with a .css file and an image chosen for 400 errors (which you will later see).
Then, a templates folder is added, with the HTML pages using Jinja syntax, and an example of a docx. template for legal documents.
Finally, the project folder itself holds the app file, written in Python, the helpers (a simplified version of the ones used in pset9 Finance challenge, the requirements and the README document. This is just the beginning, since many functionalities can be later added!
##### Page Walkthrough
The page has a homepage where it briefly explains the function and purpose of the web application. It is based in the structure proposed in the pset9 "Finance" web app from CS50x, as it portrays a friendly and minimalistic aesthetic.

As a first document, an NDA or non-disclosure agreement in Spanish is being used as a template for a full document. Accessing the navigation bar link "NDA", it is possible to fill in the form and obtain a fully functional NDA. This is made with the help of the mailmerge module available at: <https://pypi.org/project/docx-mailmerge/> The page uses a legal template customized by myself.

As it can be seen, the page shows that it is in construction. There are many things to be added to this core: the possibility of making several documents with the help of SQL, adding other legal templates, other languages and legal systems. This is just the beggining, but Shakira will be working on it!

![!(static/shakira template.jpg)](static/shakira%20template.jpg)