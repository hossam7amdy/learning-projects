/*! For license information please see 4.903901b3.chunk.js.LICENSE.txt */
(this["webpackJsonpreact-complete-guide"]=this["webpackJsonpreact-complete-guide"]||[]).push([[4],{38:function(t,e,r){"use strict";r.d(e,"b",(function(){return n})),r.d(e,"a",(function(){return o}));var n=10,o="https://http-react-50688-default-rtdb.firebaseio.com"},39:function(t,e,r){"use strict";function n(t,e,r,n,o,i,c){try{var a=t[i](c),u=a.value}catch(s){return void r(s)}a.done?e(u):Promise.resolve(u).then(n,o)}function o(t){return function(){var e=this,r=arguments;return new Promise((function(o,i){var c=t.apply(e,r);function a(t){n(c,o,i,a,u,"next",t)}function u(t){n(c,o,i,a,u,"throw",t)}a(void 0)}))}}r.d(e,"a",(function(){return o}))},40:function(t,e,r){"use strict";function n(t){return n="function"==typeof Symbol&&"symbol"==typeof Symbol.iterator?function(t){return typeof t}:function(t){return t&&"function"==typeof Symbol&&t.constructor===Symbol&&t!==Symbol.prototype?"symbol":typeof t},n(t)}function o(){o=function(){return t};var t={},e=Object.prototype,r=e.hasOwnProperty,i="function"==typeof Symbol?Symbol:{},c=i.iterator||"@@iterator",a=i.asyncIterator||"@@asyncIterator",u=i.toStringTag||"@@toStringTag";function s(t,e,r){return Object.defineProperty(t,e,{value:r,enumerable:!0,configurable:!0,writable:!0}),t[e]}try{s({},"")}catch(P){s=function(t,e,r){return t[e]=r}}function f(t,e,r,n){var o=e&&e.prototype instanceof d?e:d,i=Object.create(o.prototype),c=new E(n||[]);return i._invoke=function(t,e,r){var n="suspendedStart";return function(o,i){if("executing"===n)throw new Error("Generator is already running");if("completed"===n){if("throw"===o)throw i;return S()}for(r.method=o,r.arg=i;;){var c=r.delegate;if(c){var a=O(c,r);if(a){if(a===h)continue;return a}}if("next"===r.method)r.sent=r._sent=r.arg;else if("throw"===r.method){if("suspendedStart"===n)throw n="completed",r.arg;r.dispatchException(r.arg)}else"return"===r.method&&r.abrupt("return",r.arg);n="executing";var u=l(t,e,r);if("normal"===u.type){if(n=r.done?"completed":"suspendedYield",u.arg===h)continue;return{value:u.arg,done:r.done}}"throw"===u.type&&(n="completed",r.method="throw",r.arg=u.arg)}}}(t,r,c),i}function l(t,e,r){try{return{type:"normal",arg:t.call(e,r)}}catch(P){return{type:"throw",arg:P}}}t.wrap=f;var h={};function d(){}function p(){}function y(){}var v={};s(v,c,(function(){return this}));var b=Object.getPrototypeOf,m=b&&b(b(_([])));m&&m!==e&&r.call(m,c)&&(v=m);var g=y.prototype=d.prototype=Object.create(v);function j(t){["next","throw","return"].forEach((function(e){s(t,e,(function(t){return this._invoke(e,t)}))}))}function w(t,e){function o(i,c,a,u){var s=l(t[i],t,c);if("throw"!==s.type){var f=s.arg,h=f.value;return h&&"object"==n(h)&&r.call(h,"__await")?e.resolve(h.__await).then((function(t){o("next",t,a,u)}),(function(t){o("throw",t,a,u)})):e.resolve(h).then((function(t){f.value=t,a(f)}),(function(t){return o("throw",t,a,u)}))}u(s.arg)}var i;this._invoke=function(t,r){function n(){return new e((function(e,n){o(t,r,e,n)}))}return i=i?i.then(n,n):n()}}function O(t,e){var r=t.iterator[e.method];if(void 0===r){if(e.delegate=null,"throw"===e.method){if(t.iterator.return&&(e.method="return",e.arg=void 0,O(t,e),"throw"===e.method))return h;e.method="throw",e.arg=new TypeError("The iterator does not provide a 'throw' method")}return h}var n=l(r,t.iterator,e.arg);if("throw"===n.type)return e.method="throw",e.arg=n.arg,e.delegate=null,h;var o=n.arg;return o?o.done?(e[t.resultName]=o.value,e.next=t.nextLoc,"return"!==e.method&&(e.method="next",e.arg=void 0),e.delegate=null,h):o:(e.method="throw",e.arg=new TypeError("iterator result is not an object"),e.delegate=null,h)}function x(t){var e={tryLoc:t[0]};1 in t&&(e.catchLoc=t[1]),2 in t&&(e.finallyLoc=t[2],e.afterLoc=t[3]),this.tryEntries.push(e)}function L(t){var e=t.completion||{};e.type="normal",delete e.arg,t.completion=e}function E(t){this.tryEntries=[{tryLoc:"root"}],t.forEach(x,this),this.reset(!0)}function _(t){if(t){var e=t[c];if(e)return e.call(t);if("function"==typeof t.next)return t;if(!isNaN(t.length)){var n=-1,o=function e(){for(;++n<t.length;)if(r.call(t,n))return e.value=t[n],e.done=!1,e;return e.value=void 0,e.done=!0,e};return o.next=o}}return{next:S}}function S(){return{value:void 0,done:!0}}return p.prototype=y,s(g,"constructor",y),s(y,"constructor",p),p.displayName=s(y,u,"GeneratorFunction"),t.isGeneratorFunction=function(t){var e="function"==typeof t&&t.constructor;return!!e&&(e===p||"GeneratorFunction"===(e.displayName||e.name))},t.mark=function(t){return Object.setPrototypeOf?Object.setPrototypeOf(t,y):(t.__proto__=y,s(t,u,"GeneratorFunction")),t.prototype=Object.create(g),t},t.awrap=function(t){return{__await:t}},j(w.prototype),s(w.prototype,a,(function(){return this})),t.AsyncIterator=w,t.async=function(e,r,n,o,i){void 0===i&&(i=Promise);var c=new w(f(e,r,n,o),i);return t.isGeneratorFunction(r)?c:c.next().then((function(t){return t.done?t.value:c.next()}))},j(g),s(g,u,"Generator"),s(g,c,(function(){return this})),s(g,"toString",(function(){return"[object Generator]"})),t.keys=function(t){var e=[];for(var r in t)e.push(r);return e.reverse(),function r(){for(;e.length;){var n=e.pop();if(n in t)return r.value=n,r.done=!1,r}return r.done=!0,r}},t.values=_,E.prototype={constructor:E,reset:function(t){if(this.prev=0,this.next=0,this.sent=this._sent=void 0,this.done=!1,this.delegate=null,this.method="next",this.arg=void 0,this.tryEntries.forEach(L),!t)for(var e in this)"t"===e.charAt(0)&&r.call(this,e)&&!isNaN(+e.slice(1))&&(this[e]=void 0)},stop:function(){this.done=!0;var t=this.tryEntries[0].completion;if("throw"===t.type)throw t.arg;return this.rval},dispatchException:function(t){if(this.done)throw t;var e=this;function n(r,n){return c.type="throw",c.arg=t,e.next=r,n&&(e.method="next",e.arg=void 0),!!n}for(var o=this.tryEntries.length-1;o>=0;--o){var i=this.tryEntries[o],c=i.completion;if("root"===i.tryLoc)return n("end");if(i.tryLoc<=this.prev){var a=r.call(i,"catchLoc"),u=r.call(i,"finallyLoc");if(a&&u){if(this.prev<i.catchLoc)return n(i.catchLoc,!0);if(this.prev<i.finallyLoc)return n(i.finallyLoc)}else if(a){if(this.prev<i.catchLoc)return n(i.catchLoc,!0)}else{if(!u)throw new Error("try statement without catch or finally");if(this.prev<i.finallyLoc)return n(i.finallyLoc)}}}},abrupt:function(t,e){for(var n=this.tryEntries.length-1;n>=0;--n){var o=this.tryEntries[n];if(o.tryLoc<=this.prev&&r.call(o,"finallyLoc")&&this.prev<o.finallyLoc){var i=o;break}}i&&("break"===t||"continue"===t)&&i.tryLoc<=e&&e<=i.finallyLoc&&(i=null);var c=i?i.completion:{};return c.type=t,c.arg=e,i?(this.method="next",this.next=i.finallyLoc,h):this.complete(c)},complete:function(t,e){if("throw"===t.type)throw t.arg;return"break"===t.type||"continue"===t.type?this.next=t.arg:"return"===t.type?(this.rval=this.arg=t.arg,this.method="return",this.next="end"):"normal"===t.type&&e&&(this.next=e),h},finish:function(t){for(var e=this.tryEntries.length-1;e>=0;--e){var r=this.tryEntries[e];if(r.finallyLoc===t)return this.complete(r.completion,r.afterLoc),L(r),h}},catch:function(t){for(var e=this.tryEntries.length-1;e>=0;--e){var r=this.tryEntries[e];if(r.tryLoc===t){var n=r.completion;if("throw"===n.type){var o=n.arg;L(r)}return o}}throw new Error("illegal catch attempt")},delegateYield:function(t,e,r){return this.delegate={iterator:_(t),resultName:e,nextLoc:r},"next"===this.method&&(this.arg=void 0),h}},t}r.d(e,"a",(function(){return o}))},41:function(t,e,r){"use strict";var n=r(40),o=r(39),i=r(42),c=r(0),a=r(38),u=function(t){return new Promise((function(e,r){setTimeout((function(){r(new Error("Request timeout after ".concat(t," seconds. Try again!")))}),1e3*t)}))};e.a=function(){var t=arguments.length>0&&void 0!==arguments[0]?arguments[0]:void 0,e=Object(c.useState)(),r=Object(i.a)(e,2),s=r[0],f=r[1],l=Object(c.useState)(null),h=Object(i.a)(l,2),d=h[0],p=h[1],y=Object(c.useState)(!1),v=Object(i.a)(y,2),b=v[0],m=v[1],g=function(){var t=Object(o.a)(Object(n.a)().mark((function t(e){var r,o,i,c,s=arguments;return Object(n.a)().wrap((function(t){for(;;)switch(t.prev=t.next){case 0:return r=s.length>1&&void 0!==s[1]?s[1]:void 0,m(!0),t.prev=2,o=r?fetch(e,{method:r.method,headers:r.headers,body:JSON.stringify(r.body)}):fetch(e),t.next=6,Promise.race([o,u(a.b)]);case 6:if((i=t.sent).ok){t.next=9;break}throw new Error("Something went wrong");case 9:return t.next=11,i.json();case 11:c=t.sent,f(c),t.next=18;break;case 15:t.prev=15,t.t0=t.catch(2),p(t.t0.message);case 18:return t.prev=18,m(!1),t.finish(18);case 21:case"end":return t.stop()}}),t,null,[[2,15,18,21]])})));return function(e){return t.apply(this,arguments)}}();return Object(c.useEffect)((function(){g(t)}),[t]),{data:s,error:d,isLoading:b,fetchAPI:g}}},42:function(t,e,r){"use strict";function n(t,e){(null==e||e>t.length)&&(e=t.length);for(var r=0,n=new Array(e);r<e;r++)n[r]=t[r];return n}function o(t,e){return function(t){if(Array.isArray(t))return t}(t)||function(t,e){var r=null==t?null:"undefined"!==typeof Symbol&&t[Symbol.iterator]||t["@@iterator"];if(null!=r){var n,o,i=[],c=!0,a=!1;try{for(r=r.call(t);!(c=(n=r.next()).done)&&(i.push(n.value),!e||i.length!==e);c=!0);}catch(u){a=!0,o=u}finally{try{c||null==r.return||r.return()}finally{if(a)throw o}}return i}}(t,e)||function(t,e){if(t){if("string"===typeof t)return n(t,e);var r=Object.prototype.toString.call(t).slice(8,-1);return"Object"===r&&t.constructor&&(r=t.constructor.name),"Map"===r||"Set"===r?Array.from(t):"Arguments"===r||/^(?:Ui|I)nt(?:8|16|32)(?:Clamped)?Array$/.test(r)?n(t,e):void 0}}(t,e)||function(){throw new TypeError("Invalid attempt to destructure non-iterable instance.\nIn order to be iterable, non-array objects must have a [Symbol.iterator]() method.")}()}r.d(e,"a",(function(){return o}))},43:function(t,e,r){"use strict";var n=r(8),o=r(44),i=r.n(o),c=r(1);e.a=function(){return Object(c.jsxs)("div",{className:i.a.noquotes,children:[Object(c.jsx)("p",{children:"No quotes found!"}),Object(c.jsx)(n.b,{to:"/new-quote",className:"btn",children:"Add a Quote"})]})}},44:function(t,e,r){t.exports={noquotes:"NoQuotesFound_noquotes__18sQf"}},45:function(t,e,r){"use strict";function n(t,e,r){return e in t?Object.defineProperty(t,e,{value:r,enumerable:!0,configurable:!0,writable:!0}):t[e]=r,t}function o(t,e){var r=Object.keys(t);if(Object.getOwnPropertySymbols){var n=Object.getOwnPropertySymbols(t);e&&(n=n.filter((function(e){return Object.getOwnPropertyDescriptor(t,e).enumerable}))),r.push.apply(r,n)}return r}function i(t){for(var e=1;e<arguments.length;e++){var r=null!=arguments[e]?arguments[e]:{};e%2?o(Object(r),!0).forEach((function(e){n(t,e,r[e])})):Object.getOwnPropertyDescriptors?Object.defineProperties(t,Object.getOwnPropertyDescriptors(r)):o(Object(r)).forEach((function(e){Object.defineProperty(t,e,Object.getOwnPropertyDescriptor(r,e))}))}return t}r.d(e,"a",(function(){return i}))},46:function(t,e,r){t.exports={item:"QuoteItem_item__1904b"}},47:function(t,e,r){t.exports={list:"QuoteList_list__3I4U1",sorting:"QuoteList_sorting__2IyrZ"}},56:function(t,e,r){"use strict";r.r(e);var n=r(45),o=r(43),i=r(0),c=r(2),a=r(8),u=r(46),s=r.n(u),f=r(1),l=function(t){return Object(f.jsxs)("li",{className:s.a.item,children:[Object(f.jsxs)("figure",{children:[Object(f.jsx)("blockquote",{children:Object(f.jsx)("p",{children:t.text})}),Object(f.jsx)("figcaption",{children:t.author})]}),Object(f.jsx)(a.b,{to:"/quotes/".concat(t.id),className:"btn",children:"View Fullscreen"})]})},h=r(47),d=r.n(h),p=function(t){var e,r=Object(c.h)(),n=Object(c.i)(),o="asc"===new URLSearchParams(n.search).get("sort"),a=(e=t.quotes,o?e.sort((function(t,e){return t.id<e.id?1:-1})):e.sort((function(t,e){return t.id>e.id?1:-1})));return Object(f.jsxs)(i.Fragment,{children:[Object(f.jsx)("div",{className:d.a.sorting,children:Object(f.jsxs)("button",{onClick:function(){r.push({pathname:n.pathname,search:"sort=".concat(o?"desc":"asc")})},children:["Sort ",o?"Descending":"Ascending"]})}),Object(f.jsx)("ul",{className:d.a.list,children:a.map((function(t){return Object(f.jsx)(l,{id:t.id,author:t.author,text:t.text},t.id)}))})]})},y=r(14),v=r(41),b=r(38);e.default=function(){var t=Object(v.a)("".concat(b.a,"/quotes.json")),e=t.data,r=t.error,i=t.isLoading,c=[];for(var a in e){var u=Object(n.a)({id:a},e[a]);c.push(u)}return i?Object(f.jsxs)("div",{className:"centered",children:[Object(f.jsx)(y.a,{}),";"]}):r?Object(f.jsx)("div",{className:"centered focused",children:r||"something went wrong\ud83d\udca5\ud83d\udca5\ud83d\udca5"}):0===c.length?Object(f.jsx)(o.a,{}):Object(f.jsx)(p,{quotes:c})}}}]);
//# sourceMappingURL=4.903901b3.chunk.js.map