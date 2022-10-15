import icons from 'url:../../img/icons.svg';
import View from './View.js';

class PaginationView extends View {
  _parentElement = document.querySelector('.pagination');

  _generateMarkup() {
    const curPage = this._data.page;
    const numPages = Math.ceil(
      this._data.result.length / this._data.resultsPerPage
    );
    // 1) page 1 + others
    if (curPage === 1 && numPages > 1) return this._generateNextButton(curPage);

    // 2) middle
    if (numPages > curPage)
      return (
        this._generatePrevButton(curPage) + this._generateNextButton(curPage)
      );

    // 3) last page
    if (curPage === numPages && numPages > 1)
      return this._generatePrevButton(curPage);

    // 4) only 1 page
    return '';
  }

  _generateNextButton(curPage) {
    return `
      <button data-goto="${
        curPage + 1
      }" class="btn--inline pagination__btn--next">
        <span>Page ${curPage + 1}</span>
        <svg class="search__icon">
          <use href="${icons}#icon-arrow-right"></use>
        </svg>
      </button>
    `;
  }

  _generatePrevButton(curPage) {
    return `
      <button data-goto="${
        curPage - 1
      }" class="btn--inline pagination__btn--prev">
        <svg class="search__icon">
          <use href="${icons}#icon-arrow-left"></use>
        </svg>
        <span>Page ${curPage - 1}</span>
      </button>
    `;
  }

  addHandlerClick(handler) {
    this._parentElement.addEventListener('click', function (e) {
      const btnPagination = e.target.closest('.btn--inline');
      if (!btnPagination) return;

      const goToPage = +btnPagination.dataset.goto;
      handler(goToPage);
    });
  }
}

export default new PaginationView();
