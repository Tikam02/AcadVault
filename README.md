# AcadVault


![alt tex](https://github.com/Tikam02/AcadVault/blob/master/img/cover.png)

---

## Project Objective

AcadVault is a living open-source repository of academic files associated with the programmes offered at [DAIICT, Gandhinagar](https://www.daiict.ac.in). Every student, over the course of their programme take various courses spread across multiple domain areas. Classroom pedagogy mainly revolves around oral lectures which are often supplemented by lab sessions which allow students to gain hands-on experience about the subject. Lectures might also be supplemented by tutorial sessions which aim to strengthen the theoretical foundations of the subject. Students are graded using commonly known assesment techniques such as written examinations, lab examinations, course projects, take-home assignments, and term papers. Over the course of a programme every student creates and peruses a sizeable corpus of academic resources. These resources may include, but are not limited to lecture notes, past examination papers, course projects, tutorial solutions, etc. This repository aims to crowdsource said resources from the student body and create a common reference point to access all of these.

## Project Structure

The project organization has been designed to maximise maintainability and acessibility while minimizing overheads associated with maintainence edits and fixes. It is understood that each faculty teaches a particular course in their own way and hence courses folder have also been segregated by faculty who taught the course in the particular year.

### Directory Structure

- `IT` (Course domain prefixes such as CT, HM, etc.)
  - `107_calculus` (Course code and name, refrain from using abbreviations)
    - `reference_material` (textbooks, papers, etc.)
    - `ashok_kumar` (Faculty name, refrain from using abbreviations)
      - `2016` (Year)
        - `lecture_notes`
        - `lab_sessions`
        - `tutorial_sessions`
        - `assignments`
        - `exam_papers`
        - `projects`
        - `misc` (uncategorized material)

### Directory Nomenclature

This project follows a [`snake_case`](https://en.wikipedia.org/wiki/Snake_case) naming convention for directories throughout the project. No capital letters must be used. No exceptions.

### File Nomenclature

While there are no hard guidelines for file nomenclature we expect the contributor to name the files so that they are uniquely identifiable among material in the same directory.

## Contribution

We wholeheartedly welcome contributions of all sizes and would love to help you upload resources in an organized manner. While contributing please take care of the following points -

- Ensure that files are contributed to the exact folder where they belong
- Ensure that no duplicates are being uploaded
- In case of new courses, ensure that the contribution conforms to directory sturucture
- Refrain from creating contributions with unorganized file dumps. 

To contribute resources fork this repository and open a PR with the title `Add resources [your github username]`. A project maintainer will guide you through the PR process suggesting modifications required (if any) to conform with the project guidelines. Please open an issue in case you want suggest an enhancement, file a bug report or reach out to the maintainers any queries.

We understand that there have been unfortunate cases in the past where material has been circulated widely without the permission of the author. If you see your material that belongs to you but you did not intend to share, please file an issue describing the situation and we will take it down.

## How to contribute

The size of this repo would be pretty huge. So rather than cloning, using the Github website to make contributions seem to be the best option.

### Option - 1 : Fork and Upload.

1. Fork this repository.

2. Create a branch in YOUR FORKED REPO.

3. Upload files to that branch.

4. Open a pull request from YOUR BRANCH to this [repo](https://github.com/Tikam02/AcadVault.git).

### Option - 2 : Clone and PR

- If you have files larger than 100 Mb or not able to upload directly from browser you can use this method.

1. Fork this repository
   
2. Clone your forked repository
   > git clone https://github.com/username/AcadVault.git

3. Create a branch in your local system with your branch name
   >  git checkout -b [name_of_your_new_branch]

4. Add resources 
   > git add .

5. Commit 
   > git commit -m "your message"

6. Push into the branch
   > git push origin [name_of_your_new_branch]

7. Open a PR with the title `Add resources [your github username]`


## Maintainers

- [@Tikam02](https://github.com/Tikam02)
- [@statebait](https://github.com/statebait)
- [@Kartikeya99](https://github.com/Kartikeya99)
- [@smit2k14](https://github.com/smit2k14)
- [@gauravsofat](https://github.com/gauravsofat)




